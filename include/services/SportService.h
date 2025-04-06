#ifndef SPORT_SERVICE_H
#define SPORT_SERVICE_H

#include <vector>
#include "models/Sport.h"
#include "utils/ILogger.h"

class SportService
{
public:
    explicit SportService(ILogger& logger) : _logger(logger) {}

    [[nodiscard]] std::vector<Sport> getSports();

private:
    ILogger& _logger;
};

#endif // SPORT_SERVICE_H