#ifndef SPORT_SERVICE_H
#define SPORT_SERVICE_H

#include "Sport.h"
#include <string>
#include <vector>
#include "Logger.h"

class SportService
{
public:
    explicit SportService(Logger& logger) : logger_(logger) {}

    std::vector<Sport> getSports();

private:
    Logger& logger_;
};



#endif // SPORT_SERVICE_H