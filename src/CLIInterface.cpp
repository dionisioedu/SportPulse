#include "CLIInterface.h"
#include <stdio.h>

CLIInterface::CLIInterface(LeagueService& leagueService, SportService& sportService, ILogger& logger)
    : _leagueService(leagueService), _sportService(sportService), _logger(logger) {}

void CLIInterface::run() {
    int option = -1;

    while (option != 0) {
        std::cout << "\n--- Sport Pulse CLI Panel --\n";
        std::cout << "1. List Leagues\n";
        std::cout << "2. List Sports\n";
        std::cout << "\n0. Exit\n";
        std::cout << "\nSelect an option: ";
        std::cin >> option;

        switch (option) {
            case 1: {
                _logger.log(ILogger::Level::INFO, "User selected: List Leagues");
                std::cout << "Fetching leagues data...\n";
                auto leagues = _leagueService.getLeagues();
                if (!leagues.empty()) {
                    std::cout << "\nLeagues:\n";
                    for (const auto& league : leagues) {
                        std::cout << "ID: " << league.idLeague << " - " << league.strLeague << "\n";
                    }
                } else {
                    std::cout << "No leagues data available.\n";
                }

                break;
            }

            case 2: {
                _logger.log(ILogger::Level::INFO, "User selected: List Sports");
                std::cout << "Fetching sports data...\n";
                auto sports = _sportService.getSports();
                if (!sports.empty()) {
                    std::cout << "\nSports\n";
                    for (const auto& sport : sports) {
                        std::cout << "ID: " << sport.idSport << " - " << sport.strSport << "\n";
                    }
                } else {
                    std::cout << "No sports data available.\n";
                }

                break;
            }

            case 0: {
                _logger.log(ILogger::Level::INFO, "User selected: Exit");
                std::cout << "Exiting...\n";
                break;
            }

            default:
                std::cout << "Invalid option. Please try again\n";
                break;
        }
    }
}
