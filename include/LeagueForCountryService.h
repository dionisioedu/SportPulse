#ifndef LEAGUE_FOR_COUNTRY_SERVICE_H
#define LEAGUE_FOR_COUNTRY_SERVICE_H

#include "LeagueForCountry.h"
#include <vector>
#include "ILogger.h"

class LeagueForCountryService {
public:
    explicit LeagueForCountryService(ILogger& logger) : _logger(logger) {}

    std::vector<LeagueForCountry> getAllLeaguesForCountry(std::string country);

private:
    ILogger& _logger;
};

#endif // LEAGUE_FOR_COUNTRY_SERVICE_H