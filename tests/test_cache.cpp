#include <gtest/gtest.h>
#include "utils/Cache.h"
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

TEST(CacheTest, PutAndGet) {
    Cache<std::string, std::string> cache;
    cache.put("key", "value", 1s);
    ASSERT_EQ(cache.get("key"), "value");
}

TEST(CacheTest, Expire) {
    Cache<std::string, std::string> cache;
    cache.put("key", "value", 1s);
    std::this_thread::sleep_for(2s);
    ASSERT_EQ(cache.get("key"), std::nullopt);
}

TEST(CacheTest, Replace) {
    Cache<std::string, std::string> cache;
    cache.put("key", "value", 1s);
    cache.put("key", "new_value", 1s);
    ASSERT_EQ(cache.get("key"), "new_value");
}