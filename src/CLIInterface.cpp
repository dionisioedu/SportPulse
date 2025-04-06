#include "CLIInterface.h"
#include <iostream>

CLIInterface::CLIInterface(
    LeagueService& leagueService,
    SportService& sportService,
    CountryService& countryService,
    LeagueForCountryService& leagueForCountryService,
    SearchService& searchService,
    ILogger& logger)
    : _leagueService(leagueService),
      _sportService(sportService),
      _countryService(countryService),
      _leagueForCountryService(leagueForCountryService),
      _searchService(searchService),
      _logger(logger) {}

void CLIInterface::run() {
    int option = -1;

    while (option != 0) {
        std::cout << "\n--- Sport Pulse CLI Panel --\n";
        std::cout << "1. List Leagues\n";
        std::cout << "2. List Sports\n";
        std::cout << "3. List Countries\n";
        std::cout << "4. List Leagues for Country\n";
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

            case 3: {
                _logger.log(ILogger::Level::INFO, "User selected: List Countries");
                std::cout << "Fetching countries data...\n";
                auto countries = _countryService.getCountries();
                if (!countries.empty()) {
                    std::cout << "\nCountries\n";
                    for (const auto& country : countries) {
                        std::cout << "Name: " << country.name << " - " << country.flag_url << "\n";
                    }
                } else {
                    std::cout << "No countries data available.\n";
                }

                break;
            }

            case 4: {
                _logger.log(ILogger::Level::INFO, "User selected: List Leagues For Country");

                std::string country;
                std::cout << "Please enter a valid country name: ";
                std::cin >> country;

                std::string sport;
                std::cout << "\nPlease enter a valid sport: ";
                std::cin.ignore();
                std::getline(std::cin, sport);

                std::cout << "Fetching leagues for country data for " << country << "...\n";
                auto leagues = _leagueForCountryService.getAllLeaguesForCountry(country, sport);
                if (!leagues.empty()) {
                    std::cout << "\nLeagues\n";
                    for (const auto& league : leagues) {
                        std::cout << "ID: " << league.idLeague << " - " << league.strLeague << "\n";
                    }
                } else {
                    std::cout << "No countries data available.\n";
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
