#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <string>
#include <vector>

class ApiClient {
private:
    const std::string apiUrl = "https://www.thesportsdb.com/api/v1/json/3/";
public:
    std::string fetchLiveScores();
    std::string getAllSports();
    std::string getAllLeagues();
    std::string getAllCountries();
};

#endif // API_CLIENT_H