#include <gtest/gtest.h>
#include "services/LeagueService.h"
#include "FakeLogger.h"
#include "FakeApiClient.h"

TEST(LeagueServiceTest, GetLeaguesReturnsData) {
    FakeLogger logger;
    FakeApiClient apiClient;
    LeagueService service(logger, apiClient);
    std::vector<League> result = service.getLeagues();
    EXPECT_FALSE(result.empty());
}

TEST(LeagueServiceTest, GetLeaguesForCountryReturnsData) {
    FakeLogger logger;
    FakeApiClient apiClient;
    LeagueService service(logger, apiClient);
    std::vector<League> result = service.getAllLeaguesForCountry("Brazil");
    EXPECT_FALSE(result.empty());
}

TEST(LeagueServiceTest, GetLeaguesForCountryAndSportReturnsData) {
    FakeLogger logger;
    FakeApiClient apiClient;
    LeagueService service(logger, apiClient);
    auto result = service.getAllLeaguesForCountry("Brazil", "Soccer");
    EXPECT_FALSE(result.empty());

    for_each(result.begin(), result.end(), [](const auto& item) {
        EXPECT_STREQ(item.strSport.c_str(), "Soccer");
    });
}

TEST(LeagueServiceTest, GetLeague) {
    FakeLogger logger;
    FakeApiClient apiClient;
    LeagueService service(logger, apiClient);
    League result;
    ASSERT_NO_THROW( result = service.getLeague("4348") );
    EXPECT_FALSE(result.idLeague.empty());
}