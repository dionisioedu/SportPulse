#include <gtest/gtest.h>
#include "LeagueForCountryService.h"

class FakeLogger : public ILogger {
public:
    std::vector<std::string> logs;

    void log(Level level, const std::string& message) override {}
};

TEST(LeagueForCountryServiceTest, GetLeaguesForCountryReturnsData) {
    FakeLogger logger;
    LeagueForCountryService service(logger);
    std::vector<LeagueForCountry> result = service.getAllLeaguesForCountry("Brazil");
    EXPECT_FALSE(result.empty());
}