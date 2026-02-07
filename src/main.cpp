#include <iostream>
#include <thread>
#include <chrono>
#include "CLIInterface.h"
#include "apis/TheSportsDbApiClient.h"
#include "services/SportService.h"
#include "services/LeagueService.h"
#include "services/CountryService.h"
#include "services/SearchService.h"
#include "RestServer.h"
#include "utils/Cache.h"
#include "utils/Logger.h"

int main(int argc, char* argv[]) {
    Logger logger("sportpulse.log");
    logger.log(ILogger::Level::INFO, "Starting SportPulse");

    // Initialize services with the injected logger
    SportService sportService(logger);
    LeagueService leagueService(logger);
    CountryService countryService(logger);

    TheSportsDbApiClient apiClient;
    SearchService searchService(logger, apiClient);

    // Parse command-line arguments to decide mode: --api, --cli, or both.
    bool runApi = false;
    bool runCli = false;
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (arg == "--api") {
            runApi = true;
        } else if (arg == "--cli") {
            runCli = true;
        }
    }
    // Default: if no arguments provided, run API only.
    if (!runApi && !runCli) {
        runApi = true;
    }

    // Pointer to RestServer to control its lifetime.
    RestServer* restServer = nullptr;
    std::thread restThread;
    if (runApi) {
        utility::string_t address = U("http://0.0.0.0:8080/");
        restServer = new RestServer(
            address,
            leagueService,
            sportService,
            countryService,
            searchService,
            logger);

        restThread = std::thread([&]() {
            try {
                restServer->start();
            } catch (const std::exception& e) {
                std::cerr << "Error starting REST server: " << e.what() << std::endl;
            }
        });
    }

    if (runCli) {
        CLIInterface cli(
            leagueService,
            sportService,
            countryService,
            searchService,
            logger);

        cli.run();
    } else {
        logger.log(ILogger::Level::INFO, "API is running. Waiting for termination signal...");
        while (true) {
            std::this_thread::sleep_for(std::chrono::hours(1));
        }
    }

    if (runApi) {
        restServer->stop();
        if (restThread.joinable())
            restThread.join();
        delete restServer;
    }

    logger.log(ILogger::Level::INFO, "SportPulse stopped");
    return 0;
}
