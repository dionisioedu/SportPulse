#include <gtest/gtest.h>
#include "services/SportService.h"

class FakeLogger : public ILogger {
public:
    std::vector<std::string> logs;

    void log(Level level, const std::string& message) override {}
};

TEST(SportServiceTest, GetSportsReturnsData) {
    FakeLogger logger;
    SportService service(logger);
    std::vector<Sport> result = service.getSports();
    // Ensure that the result is not empty. Adjust as needed based on expected response.
    EXPECT_FALSE(result.empty());
}