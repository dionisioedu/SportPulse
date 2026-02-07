#include <gtest/gtest.h>
#include "services/SportService.h"
#include "FakeLogger.h"
#include "FakeApiClient.h"

TEST(SportServiceTest, GetSportsReturnsData) {
    FakeLogger logger;
    FakeApiClient apiClient;
    SportService service(logger, apiClient);
    std::vector<Sport> result = service.getSports();
    // Ensure that the result is not empty. Adjust as needed based on expected response.
    EXPECT_FALSE(result.empty());
    EXPECT_TRUE(logger.logs.size() > 0);
}