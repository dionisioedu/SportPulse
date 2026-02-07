#pragma once

#include <vector>
#include <string>
#include <mutex>
#include "models/Post.h"
#include "utils/ILogger.h"

class PostService {
public:
    explicit PostService(ILogger& logger);

    // cursor-based paging (cursor = offset string)
    [[nodiscard]] std::pair<std::vector<Post>, std::string> getPosts(int limit, const std::string& cursor);

    // delta sync: return posts where publishedAt > since
    [[nodiscard]] std::vector<Post> getUpdates(long long sinceEpochSec, int limit);

    [[nodiscard]] long long serverTimeEpochSec() const;

private:
    void loadMockPosts();

    ILogger& _logger;
    mutable std::mutex _mtx;
    std::vector<Post> _posts; // newest first (publishedAt desc)
};
