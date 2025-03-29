#ifndef LEAGUE_SERVICE_H
#define LEAGUE_SERVICE_H

#include "League.h"
#include <string>
#include <vector>
#include "ILogger.h"

class LeagueService {
public:
    explicit LeagueService(ILogger& logger) : _logger(logger) {}

    std::vector<League> getLeagues();

private:
    ILogger& _logger;
};

#endif // LEAGUE_SERVICE_H