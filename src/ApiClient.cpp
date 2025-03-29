#include "ApiClient.h"
#include <curl/curl.h>
#include <sstream>

size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string ApiClient::fetchLiveScores() {
    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        const std::string url = apiUrl + "eventslast.php?id=133602";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

std::string ApiClient::getAllSports() {
    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        const std::string url = apiUrl + "all_sports.php";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

std::string ApiClient::getAllLeagues() {
    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        const std::string url = apiUrl + "all_leagues.php";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

std::string ApiClient::getAllCountries() {
    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        const std::string url = apiUrl + "all_countries.php";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}