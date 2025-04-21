#include <gtest/gtest.h>
#include "services/LeagueService.h"

class FakeLogger : public ILogger {
public:
    std::vector<std::string> logs;

    void log(Level level, const std::string& message) override {}
};

TEST(LeagueServiceTest, GetLeaguesReturnsData) {
    FakeLogger logger;
    LeagueService service(logger);
    std::vector<League> result = service.getLeagues();
    EXPECT_FALSE(result.empty());
}

TEST(LeagueServiceTest, GetLeaguesForCountryReturnsData) {
    FakeLogger logger;
    LeagueService service(logger);
    std::vector<League> result = service.getAllLeaguesForCountry("Brazil");
    EXPECT_FALSE(result.empty());
}

TEST(LeagueServiceTest, GetLeaguesForCountryAndSportReturnsData) {
    FakeLogger logger;
    LeagueService service(logger);
    auto result = service.getAllLeaguesForCountry("Brazil", "Soccer");
    EXPECT_FALSE(result.empty());

    for_each(result.begin(), result.end(), [](const auto& item) {
        EXPECT_STREQ(item.strSport.c_str(), "Soccer");
    });
}

TEST(LeagueServiceTest, GetLeague) {
    FakeLogger logger;
    LeagueService service(logger);
    League result;
    ASSERT_NO_THROW( result = service.getLeague("4348") );
    EXPECT_FALSE(result.idLeague.empty());
}