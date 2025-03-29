#ifndef CLI_INTERFACE_H
#define CLI_INTERFACE_H

#include "ILogger.h"
#include "LeagueService.h"
#include "SportService.h"

class CLIInterface {
public:
    CLIInterface(LeagueService& leagueService, SportService& sportService, ILogger& logger);
    void run();

private:
    LeagueService& _leagueService;
    SportService& _sportService;
    ILogger& _logger;
};

#endif // CLI_INTERFACE_H