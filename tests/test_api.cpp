#include <gtest/gtest.h>
#include "ApiClient.h"

TEST(ApiClientTest, SearchTeamsReturnsData) {
    ApiClient client;
    std::string result = client.searchTeams("Arsenal");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, SearchTeamsByShortCodeReturnsData) {
    ApiClient client;
    std::string result = client.searchTeamsByShortCode("Arsenal");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, SearchPlayersReturnsData) {
    ApiClient client;
    std::string result = client.searchPlayers("Danny_Welbeck");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, SearchPlayersFromTeamReturnsData) {
    ApiClient client;
    std::string result = client.searchPlayersFromTeam("Arsenal");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, SearchEventByNameReturnsData) {
    ApiClient client;
    std::string result = client.searchEventByName("Arsenal_vs_Chelsea");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, SearchEventByNameAndYearReturnsData) {
    ApiClient client;
    std::string result = client.searchEventsByNameAndYear("Arsenal_vs_Chelsea", "2016", "2017");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, SearchEventByEventFileNameReturnsData) {
    ApiClient client;
    std::string result = client.searchEventByEventFileName("English_Premier_League_2015-04-26_Arsenal_vs_Chelsea");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, SearchForVenueReturnsData) {
    ApiClient client;
    std::string result = client.searchForVenue("Wembley");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, GetAllSportsReturnsData) {
    ApiClient client;
    std::string result = client.getAllSports();
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, GetAllLeaguesReturnsData) {
    ApiClient client;
    std::string result = client.getAllLeagues();
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, GetAllCountriesReturnsData) {
    ApiClient client;
    std::string result = client.getAllCountries();
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, GetLeaguesForCountryReturnsData) {
    ApiClient client;
    std::string result = client.getLeaguesForCountry("Brazil");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, GetLeaguesForCountryAndSportReturnsData) {
    ApiClient client;
    std::string result = client.getLeaguesForCountry("Brazil", "Soccer");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, GetSeasonsFromLeague) {
    ApiClient client;
    std::string result = client.getSeasonsFromLeague("4328");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, GetLeague) {
    ApiClient client;
    auto result = client.getLeague("4396");
    EXPECT_FALSE(result.empty());
}

TEST(ApiClientTest, FetchLiveScoresReturnsData) {
    ApiClient client;
    std::string result = client.fetchLiveScores();
    EXPECT_FALSE(result.empty());
}
