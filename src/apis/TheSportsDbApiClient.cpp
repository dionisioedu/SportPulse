#include "apis/TheSportsDbApiClient.h"
#include <curl/curl.h>
#include <sstream>

size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string TheSportsDbApiClient::request(const std::string endpoint) {
    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        const std::string url = apiUrl + endpoint;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

std::string TheSportsDbApiClient::searchTeams(const std::string teamName) {
    return request("searchteams.php?t=" + teamName);
}

std::string TheSportsDbApiClient::searchTeamsByShortCode(const std::string shortCode) {
    return request("searchteams.php?sname=" + shortCode);
}

std::string TheSportsDbApiClient::searchPlayers(const std::string playerName) {
    return request("searchplayers.php?p=" + playerName);
}

std::string TheSportsDbApiClient::searchPlayersFromTeam(const std::string teamName) {
    return request("searchplayers.php?t=" + teamName);
}

std::string TheSportsDbApiClient::searchEventByName(const std::string eventName) {
    return request("searchevents.php?e=" + eventName);
}

std::string TheSportsDbApiClient::searchEventsByNameAndYear(const std::string eventName, const std::string startYear, const std::string endYear) {
    return request("searchevents.php?e=" + eventName + "&=" + startYear + "-" + endYear);
}

std::string TheSportsDbApiClient::searchEventByEventFileName(const std::string eventFileName) {
    return request("searchfilename.php?e=" + eventFileName);
}

std::string TheSportsDbApiClient::searchForVenue(const std::string venueName) {
    return request("searchvenues.php?t=" + venueName);
}

std::string TheSportsDbApiClient::getAllSports() {
    return request("all_sports.php");
}

std::string TheSportsDbApiClient::getAllLeagues() {
    return request("all_leagues.php");
}

std::string TheSportsDbApiClient::getAllCountries() {
    return request("all_countries.php");
}

std::string TheSportsDbApiClient::getLeaguesForCountry(const std::string country) {
    return request("search_all_leagues.php?c=" + country);
}

std::string TheSportsDbApiClient::getLeaguesForCountry(const std::string country, const std::string sport) {
    return request("search_all_leagues.php?c=" + country + "&s=" + sport);
}

std::string TheSportsDbApiClient::getSeasonsFromLeague(const std::string leagueId) {
    return request("search_all_seasons.php?id=" + leagueId + "&badge=1");
}

std::string TheSportsDbApiClient::getLeague(const std::string leagueId) {
    return request("lookupleague.php?id=" + leagueId);
}

std::string TheSportsDbApiClient::fetchLiveScores() {
    return request("eventslast.php?id=133602");
}
