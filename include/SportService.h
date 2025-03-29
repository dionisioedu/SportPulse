#ifndef SPORT_SERVICE_H
#define SPORT_SERVICE_H

#include <vector>
#include "Sport.h"
#include "ILogger.h"

class SportService
{
public:
    explicit SportService(ILogger& logger) : _logger(logger) {}

    std::vector<Sport> getSports();

private:
    ILogger& _logger;
};

#endif // SPORT_SERVICE_H