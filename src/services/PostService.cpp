#include "services/PostService.h"

#include <algorithm>
#include <chrono>

static long long nowEpochSec() {
    using namespace std::chrono;
    return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

PostService::PostService(ILogger& logger)
    : _logger(logger) {
    loadMockPosts();
}

PostService::~PostService() {
    stopMockGenerator();
}

long long PostService::serverTimeEpochSec() const {
    return nowEpochSec();
}

void PostService::loadMockPosts() {
    std::lock_guard<std::mutex> lock(_mtx);

    const long long base = nowEpochSec();

    _posts.clear();
    _posts.reserve(10);

    // Create 10 initial mock posts (newest first).
    // IDs: mock-10 ... mock-1
    for (int i = 0; i < 10; ++i) {
        Post p;
        const int n = 10 - i;

        p.id = "mock-" + std::to_string(n);

        p.title = "SportPulse Mock Post #" + std::to_string(n);
        p.summary = "Resumo mockado para integrar o feed no frontend. "
                    "Depois vamos plugar a geração real de notícias e persistência.";

        p.imageUrl = "https://picsum.photos/seed/sportpulse_" + std::to_string(n) + "/800/450";
        p.sourceName = "SportPulse Mock";
        p.sourceUrl = "https://sportpulse.today";

        // Spread in time: newest = base, then -60s, -120s...
        p.publishedAtEpochSec = base - (i * 60);
        p.updatedAtEpochSec = p.publishedAtEpochSec;

        p.tags = {"mock", "news", "sport"};

        _posts.push_back(std::move(p));
    }

    // Ensure descending ordering by publishedAt.
    std::sort(_posts.begin(), _posts.end(),
              [](const Post& a, const Post& b) { return a.publishedAtEpochSec > b.publishedAtEpochSec; });

    // After seeding mock-1..mock-10, next generated id should start at 11.
    _nextMockId.store(11);
}

Post PostService::makeNextMockPostLocked(long long now) {
    // This function must be called with _mtx held.
    const long long idNum = _nextMockId.fetch_add(1);

    Post p;
    p.id = "mock-" + std::to_string(idNum);

    p.title = "SportPulse Mock Post #" + std::to_string(idNum);
    p.summary = "This mock post was generated automatically to simulate real-time updates in the UI.";

    // Use a deterministic image seed so each id gets a stable, different image.
    p.imageUrl = "https://picsum.photos/seed/sportpulse_" + std::to_string(idNum) + "/800/450";
    p.sourceName = "SportPulse Mock";
    p.sourceUrl = "https://sportpulse.today";

    p.publishedAtEpochSec = now;
    p.updatedAtEpochSec = now;

    p.tags = {"mock", "pulse", "sport"};

    return p;
}

void PostService::startMockGenerator(int intervalMs) {
    // Clamp interval for safety.
    if (intervalMs < 500) intervalMs = 500;

    bool expected = false;
    if (!_mockRunning.compare_exchange_strong(expected, true)) {
        // Already running.
        return;
    }

    _logger.log(ILogger::Level::INFO, "Starting mock post generator.");

    _mockWorker = std::thread([this, intervalMs]() {
        runMockLoop(intervalMs);
    });
}

void PostService::stopMockGenerator() {
    if (!_mockRunning.exchange(false)) {
        return; // Not running.
    }

    _logger.log(ILogger::Level::INFO, "Stopping mock post generator.");

    if (_mockWorker.joinable()) {
        _mockWorker.join();
    }
}

void PostService::runMockLoop(int intervalMs) {
    while (_mockRunning.load()) {
        {
            std::lock_guard<std::mutex> lock(_mtx);

            const long long t = nowEpochSec();
            Post p = makeNextMockPostLocked(t);

            // Insert at front so it's the newest.
            _posts.insert(_posts.begin(), std::move(p));

            // Keep memory bounded.
            constexpr size_t kMaxPosts = 300;
            if (_posts.size() > kMaxPosts) {
                _posts.resize(kMaxPosts);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
    }
}

std::pair<std::vector<Post>, std::string> PostService::getPosts(int limit, const std::string& cursor) {
    std::lock_guard<std::mutex> lock(_mtx);

    if (limit <= 0) limit = 10;
    if (limit > 50) limit = 50;

    int offset = 0;
    try {
        if (!cursor.empty()) offset = std::stoi(cursor);
    } catch (...) {
        offset = 0;
    }

    if (offset < 0) offset = 0;
    if (offset >= static_cast<int>(_posts.size())) {
        return {{}, ""};
    }

    const int end = std::min(offset + limit, static_cast<int>(_posts.size()));
    std::vector<Post> out;
    out.reserve(end - offset);

    for (int i = offset; i < end; ++i) out.push_back(_posts[i]);

    std::string nextCursor;
    if (end < static_cast<int>(_posts.size())) nextCursor = std::to_string(end);

    return {out, nextCursor};
}

std::vector<Post> PostService::getUpdates(long long sinceEpochSec, int limit) {
    std::lock_guard<std::mutex> lock(_mtx);

    if (limit <= 0) limit = 50;
    if (limit > 200) limit = 200;

    std::vector<Post> out;
    out.reserve(std::min(limit, static_cast<int>(_posts.size())));

    for (const auto& p : _posts) {
        if (p.publishedAtEpochSec > sinceEpochSec) {
            out.push_back(p);
            if (static_cast<int>(out.size()) >= limit) break;
        }
    }

    return out;
}
