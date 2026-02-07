#pragma once

#include <string>
#include <vector>
#include "utils/ILogger.h"
#include "IApiClient.h"
#include "models/League.h"

class LeagueService {
public:
    explicit LeagueService(ILogger& logger, IApiClient& apiClient) : _logger(logger), _apiClient(apiClient) {}

    [[nodiscard]] std::vector<League> getLeagues();
    [[nodiscard]] std::vector<League> getAllLeaguesForCountry(const std::string country, const std::string sport = "");
    [[nodiscard]] League getLeague(const std::string leagueId);

private:
    ILogger& _logger;
    IApiClient& _apiClient;
};