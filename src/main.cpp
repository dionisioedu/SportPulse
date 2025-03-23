#include <iostream>
#include <thread>
#include <chrono>
#include "SportService.h"
#include "LeagueService.h"
#include "Cache.h"
#include "Logger.h"

int main() {
    Logger logger;
    logger.log(Logger::Level::INFO, "Starting SportPulse");

    SportService sportService(logger);

    auto sports = sportService.getSports();
    logger.log(Logger::Level::INFO, "Retrieved " + std::to_string(sports.size()) + " sports");

    std::cout << "List of Sports:" << std::endl;
    for (const auto& sport : sports) {
        std::cout << sport.strSport << std::endl;
    }

    LeagueService leagueService(logger);

    auto leagues = leagueService.getLeagues();
    logger.log(Logger::Level::INFO, "Retrieved " + std::to_string(sports.size()) + " sports");

    std::cout << "List of Leagues:" << std::endl;
    for (const auto& league : leagues) {
        std::cout << league.strLeague << std::endl;
    }

    return 0;
}