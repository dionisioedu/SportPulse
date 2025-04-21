#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include "utils/ILogger.h"
#include "services/LeagueService.h"
#include "services/SportService.h"
#include "services/CountryService.h"
#include "services/SearchService.h"

class CLIInterface {
public:
    CLIInterface(
        LeagueService& leagueService,
        SportService& sportService,
        CountryService& countrySerice,
        SearchService& searchService,
        ILogger& logger);

    void run();

private:
    LeagueService& _leagueService;
    SportService& _sportService;
    CountryService& _countryService;
    SearchService& _searchService;
    ILogger& _logger;
};

#endif // CLI_INTERFACE_H