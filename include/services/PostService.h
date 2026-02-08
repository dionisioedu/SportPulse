#pragma once

#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include <atomic>

#include "models/Post.h"
#include "utils/ILogger.h"

class PostService {
public:
    explicit PostService(ILogger& logger);
    ~PostService();

    // cursor-based paging (cursor = offset string)
    [[nodiscard]] std::pair<std::vector<Post>, std::string> getPosts(int limit, const std::string& cursor);

    // delta sync: return posts where publishedAt > since
    [[nodiscard]] std::vector<Post> getUpdates(long long sinceEpochSec, int limit);

    [[nodiscard]] long long serverTimeEpochSec() const;

    // Starts/stops a background generator that creates new mock posts periodically.
    // This is meant for Phase 1 to simulate "real-time" updates in the frontend.
    void startMockGenerator(int intervalMs = 5000);
    void stopMockGenerator();

private:
    void loadMockPosts();

    // Creates a single new mock post with a unique incremental id and current timestamps.
    Post makeNextMockPostLocked(long long now);

    // Background loop that periodically generates a new mock post.
    void runMockLoop(int intervalMs);

    ILogger& _logger;
    mutable std::mutex _mtx;
    std::vector<Post> _posts; // newest first (publishedAt desc)

    std::atomic<long long> _nextMockId{11}; // first generated id after initial 10 mocks
    std::atomic<bool> _mockRunning{false};
    std::thread _mockWorker;
};
