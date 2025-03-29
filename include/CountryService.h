#ifndef COUNTRY_SERVICE_H
#define COUNTRY_SERVICE_H

#include <vector>
#include "ILogger.h"
#include "Country.h"

class CountryService {
public:
    explicit CountryService(ILogger& logger) : _logger(logger) {}

    std::vector<Country> getCountries();

private:
    ILogger& _logger;
};

#endif // COUNTRY_SERVICE_H