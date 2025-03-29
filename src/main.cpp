#include <iostream>
#include <thread>
#include <chrono>
#include "CLIInterface.h"
#include "SportService.h"
#include "LeagueService.h"
#include "Cache.h"
#include "Logger.h"

int main() {
    Logger logger;
    logger.log(Logger::Level::INFO, "Starting SportPulse");

    SportService sportService(logger);
    LeagueService leagueService(logger);
    CountryService countryService(logger);

    CLIInterface cli(leagueService, sportService, countryService, logger);
    cli.run();

    return 0;
}