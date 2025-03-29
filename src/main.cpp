#include <iostream>
#include <thread>
#include <chrono>
#include "CLIInterface.h"
#include "SportService.h"
#include "LeagueService.h"
#include "LeagueForCountryService.h"
#include "Cache.h"
#include "Logger.h"

int main() {
    Logger logger;
    logger.log(Logger::Level::INFO, "Starting SportPulse");

    SportService sportService(logger);
    LeagueService leagueService(logger);
    CountryService countryService(logger);
    LeagueForCountryService LeagueForCountryService(logger);

    CLIInterface cli(leagueService, sportService, countryService, LeagueForCountryService, logger);
    cli.run();

    return 0;
}