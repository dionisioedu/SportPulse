#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include "ILogger.h"
#include "LeagueService.h"
#include "SportService.h"
#include "CountryService.h"

class CLIInterface {
public:
    CLIInterface(
        LeagueService& leagueService,
        SportService& sportService,
        CountryService& countrySerice,
        ILogger& logger);

    void run();

private:
    LeagueService& _leagueService;
    SportService& _sportService;
    CountryService& _countryService;
    ILogger& _logger;
};

#endif // CLI_INTERFACE_H