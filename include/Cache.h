#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <chrono>
#include <optional>
#include <shared_mutex>
#include <mutex>

template <typename K, typename V>
class Cache {
public:
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;

    struct CacheEntry {
        V value;
        TimePoint expiry;
    };

    void put(const K& key, const V& value, std::chrono::seconds ttl) {
        std::unique_lock lock(mutex);
        cache[key] = {value, Clock::now() + ttl};
    }

    std::optional<V> get(const K& key) {
        std::shared_lock lock(mutex);
        auto it = cache.find(key);
        if (it == cache.end()) {
            return std::nullopt;
        }

        if (it->second.expiry < Clock::now()) {
            cache.erase(it);
            return std::nullopt;
        }

        return it->second.value;
    }

private:
    std::unordered_map<K, CacheEntry> cache;
    mutable std::shared_mutex mutex;
};

#endif // CACHE_H