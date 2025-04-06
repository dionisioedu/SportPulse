#ifndef LEAGUE_SERVICE_H
#define LEAGUE_SERVICE_H

#include <string>
#include <vector>
#include "utils/ILogger.h"
#include "models/League.h"

class LeagueService {
public:
    explicit LeagueService(ILogger& logger) : _logger(logger) {}

    [[nodiscard]] std::vector<League> getLeagues();

private:
    ILogger& _logger;
};

#endif // LEAGUE_SERVICE_H