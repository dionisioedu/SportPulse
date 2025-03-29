#ifndef LEAGUE_SERVICE_H
#define LEAGUE_SERVICE_H

#include "League.h"
#include <string>
#include <vector>
#include "ILogger.h"

class LeagueService
{
public:
    explicit LeagueService(ILogger& logger) : logger_(logger) {}

    std::vector<League> getLeagues();

private:
    ILogger& logger_;
};

#endif // LEAGUE_SERVICE_H