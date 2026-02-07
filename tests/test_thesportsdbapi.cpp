#include <gtest/gtest.h>
#include "apis/TheSportsDbApiClient.h"

TEST(TheSportsDbApiClientTest, SearchTeamsReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.searchTeams("Arsenal");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, SearchTeamsByShortCodeReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.searchTeamsByShortCode("ARS");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, SearchPlayersReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.searchPlayers("Danny_Welbeck");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, SearchPlayersFromTeamReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.searchPlayersFromTeam("Arsenal");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, SearchEventByNameReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.searchEventByName("Arsenal_vs_Chelsea");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, SearchEventByNameAndYearReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.searchEventsByNameAndYear("Arsenal_vs_Chelsea", "2016", "2017");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, SearchEventByEventFileNameReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.searchEventByEventFileName("English_Premier_League_2015-04-26_Arsenal_vs_Chelsea");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, SearchForVenueReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.searchForVenue("Wembley");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, GetAllSportsReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.getAllSports();
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, GetAllLeaguesReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.getAllLeagues();
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, GetAllCountriesReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.getAllCountries();
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, GetLeaguesForCountryReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.getLeaguesForCountry("Brazil");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, GetLeaguesForCountryAndSportReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.getLeaguesForCountry("Brazil", "Soccer");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, GetSeasonsFromLeague) {
    TheSportsDbApiClient client;
    std::string result = client.getSeasonsFromLeague("4328");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, GetLeague) {
    TheSportsDbApiClient client;
    auto result = client.getLeague("4396");
    EXPECT_FALSE(result.empty());
}

TEST(TheSportsDbApiClientTest, FetchLiveScoresReturnsData) {
    TheSportsDbApiClient client;
    std::string result = client.fetchLiveScores();
    EXPECT_FALSE(result.empty());
}
