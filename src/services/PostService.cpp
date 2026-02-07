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

long long PostService::serverTimeEpochSec() const {
    return nowEpochSec();
}

void PostService::loadMockPosts() {
    std::lock_guard<std::mutex> lock(_mtx);

    const long long base = nowEpochSec();

    _posts.clear();
    _posts.reserve(10);

    // 10 posts mockados (ordem: mais novo primeiro)
    for (int i = 0; i < 10; ++i) {
        Post p;
        p.id = "mock-" + std::to_string(10 - i);

        p.title = "SportPulse Mock Post #" + std::to_string(10 - i);
        p.summary = "Resumo mockado para integrar o feed no frontend. "
                    "Depois vamos plugar a geração real de notícias e persistência.";

        p.imageUrl = "https://picsum.photos/seed/sportpulse_" + std::to_string(10 - i) + "/800/450";
        p.sourceName = "SportPulse Mock";
        p.sourceUrl = "https://sportpulse.today";

        // espalha no tempo: mais novo = base, depois -60s, -120s...
        p.publishedAtEpochSec = base - (i * 60);
        p.updatedAtEpochSec = p.publishedAtEpochSec;

        p.tags = {"mock", "news", "sport"};

        _posts.push_back(std::move(p));
    }

    // garante ordenação desc por publishedAt
    std::sort(_posts.begin(), _posts.end(),
              [](const Post& a, const Post& b) { return a.publishedAtEpochSec > b.publishedAtEpochSec; });
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
