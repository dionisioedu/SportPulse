#ifndef LEAGUE_SERVICE_H
#define LEAGUE_SERVICE_H

#include "League.h"
#include <string>
#include <vector>
#include "Logger.h"

class LeagueService
{
public:
    explicit LeagueService(Logger& logger) : logger_(logger) {}

    std::vector<League> getLeagues();

private:
    Logger& logger_;
};

#endif // LEAGUE_SERVICE_H