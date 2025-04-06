#ifndef SEARCH_SERVICE_H
#define SEARCH_SERVICE_H

#include <string>
#include "utils/ILogger.h"
#include "IApiClient.h"
#include "models/Team.h"
#include "models/Player.h"

class SearchService {
    ILogger& log;
    IApiClient& apiClient;

public:
    explicit SearchService(ILogger& log, IApiClient& apiClient) : log(log), apiClient(apiClient) {}

    [[nodiscard]] std::vector<Team> searchTeamsByName(const std::string teamName);
    [[nodiscard]] std::vector<Team> searchTeamsByShortCode(const std::string shortCode);
    [[nodiscard]] std::vector<Player> searchPlayers(const std::string playerName);
    [[nodiscard]] std::vector<Player> searchPlayersFromTeam(const std::string teamName);

};

#endif // SEARCH_SERVICE_H