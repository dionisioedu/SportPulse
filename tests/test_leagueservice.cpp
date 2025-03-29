#include <gtest/gtest.h>
#include "LeagueService.h"

class FakeLogger : public ILogger {
public:
    std::vector<std::string> logs;

    void log(Level level, const std::string& message) override {}
};

TEST(LeagueServiceTest, GetLeaguesReturnsData) {
    FakeLogger logger;
    LeagueService service(logger);
    std::vector<League> result = service.getLeagues();
    // Ensure that the result is not empty. Adjust as needed based on expected response.
    EXPECT_FALSE(result.empty());
}