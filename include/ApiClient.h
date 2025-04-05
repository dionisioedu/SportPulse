#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <string>
#include <vector>

class ApiClient {
private:
    const std::string apiUrl = "https://www.thesportsdb.com/api/v1/json/3/";

    [[nodiscard]] std::string request(const std::string endpoint);

public:
    [[nodiscard]] std::string fetchLiveScores();
    [[nodiscard]] std::string getAllSports();
    [[nodiscard]] std::string getAllLeagues();
    [[nodiscard]] std::string getAllCountries();
    [[nodiscard]] std::string getLeaguesForCountry(const std::string country);
    [[nodiscard]] std::string getLeaguesForCountry(const std::string country, const std::string sport);
};

#endif // API_CLIENT_H