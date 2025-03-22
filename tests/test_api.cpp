#include <gtest/gtest.h>
#include "../include/ApiClient.h"

TEST(ApiClientTest, FetchLiveScoresReturnsData) {
    ApiClient client;
    std::string result = client.fetchLiveScores();
    // Ensure that the result is not empty. Adjust as needed based on expected response.
    EXPECT_FALSE(result.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
