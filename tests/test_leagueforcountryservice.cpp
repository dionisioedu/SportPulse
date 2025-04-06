#include <gtest/gtest.h>
#include "services/LeagueForCountryService.h"

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

TEST(LeagueForCountryServiceTest, GetLeaguesForCountryAndSportReturnsData) {
    FakeLogger logger;
    LeagueForCountryService service(logger);
    auto result = service.getAllLeaguesForCountry("Brazil", "Soccer");
    EXPECT_FALSE(result.empty());

    for_each(result.begin(), result.end(), [](const auto& item) {
        EXPECT_STREQ(item.strSport.c_str(), "Soccer");
    });
}