#ifndef SEARCH_SERVICE_H
#define SEARCH_SERVICE_H

#include <string>
#include "utils/ILogger.h"
#include "IApiClient.h"
#include "models/Team.h"

class SearchService {
    ILogger& log;
    IApiClient& apiClient;

public:
    explicit SearchService(ILogger& log, IApiClient& apiClient) : log(log), apiClient(apiClient) {}

    [[nodiscard]] std::vector<Team> searchTeamsByName(const std::string teamName);
    [[nodiscard]] std::vector<Team> searchTeamsByShortCode(const std::string shortCode);

};

#endif // SEARCH_SERVICE_H