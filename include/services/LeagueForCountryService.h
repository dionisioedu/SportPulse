#ifndef LEAGUE_FOR_COUNTRY_SERVICE_H
#define LEAGUE_FOR_COUNTRY_SERVICE_H

#include <vector>
#include "utils/ILogger.h"
#include "models/LeagueForCountry.h"

class LeagueForCountryService {
public:
    explicit LeagueForCountryService(ILogger& logger) : _logger(logger) {}

    [[nodiscard]] std::vector<LeagueForCountry> getAllLeaguesForCountry(std::string country, std::string sport = "");

private:
    ILogger& _logger;
};

#endif // LEAGUE_FOR_COUNTRY_SERVICE_H