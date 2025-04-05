#include <iostream>
#include <thread>
#include <chrono>
#include "CLIInterface.h"
#include "SportService.h"
#include "LeagueService.h"
#include "LeagueForCountryService.h"
#include "CountryService.h"
#include "RestServer.h"
#include "Cache.h"
#include "Logger.h"

int main() {
    Logger logger;
    logger.log(Logger::Level::INFO, "Starting SportPulse");

    SportService sportService(logger);
    LeagueService leagueService(logger);
    CountryService countryService(logger);
    LeagueForCountryService LeagueForCountryService(logger);

    utility::string_t address = U("http://0.0.0.0:8080/");
    RestServer restServer(address, leagueService, sportService, countryService, LeagueForCountryService, logger);

    std::thread restServerThread([&restServer]() {
        try {
            restServer.start();
        } catch (const std::exception& e) {
            std::cerr << "Error starting REST server: " << e.what() << std::endl;
        }
    });

    CLIInterface cli(leagueService, sportService, countryService, LeagueForCountryService, logger);
    cli.run();

    restServer.stop();
    if (restServerThread.joinable()) {
        restServerThread.join();
    }
    logger.log(Logger::Level::INFO, "SportPulse stopped");

    return 0;
}