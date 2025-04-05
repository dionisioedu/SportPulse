#include "ApiClient.h"
#include <curl/curl.h>
#include <sstream>

size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string ApiClient::request(const std::string endpoint) {
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

std::string ApiClient::fetchLiveScores() {
    return request("eventslast.php?id=133602");
}

std::string ApiClient::getAllSports() {
    return request("all_sports.php");
}

std::string ApiClient::getAllLeagues() {
    return request("all_leagues.php");
}

std::string ApiClient::getAllCountries() {
    return request("all_countries.php");
}

std::string ApiClient::getLeaguesForCountry(const std::string country) {
    return request("search_all_leagues.php?c=" + country);
}

std::string ApiClient::getLeaguesForCountry(const std::string country, const std::string sport) {
    return request("search_all_leagues.php?c=" + country + "&s=" + sport);
}