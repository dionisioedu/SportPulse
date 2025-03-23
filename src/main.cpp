#include <iostream>
#include <thread>
#include <chrono>
#include "SportService.h"
#include "Cache.h"
#include "Logger.h"

int main() {
    Logger logger;
    logger.log(Logger::Level::INFO, "Starting SportPulse");

    SportService service(logger);

    auto sports = service.getSports();
    logger.log(Logger::Level::INFO, "Retrieved " + std::to_string(sports.size()) + " sports");

    std::cout << "List of Sports:" << std::endl;
    for (const auto& sport : sports) {
        std::cout << sport.strSport << std::endl;
    }

    return 0;
}