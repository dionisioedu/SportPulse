#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <string>
#include <vector>

class ApiClient {
public:
    std::string fetchLiveScores();
    std::string getAllSports();
    std::string getAllLeagues();
};

#endif // API_CLIENT_H