#ifndef COUNTRY_SERVICE_H
#define COUNTRY_SERVICE_H

#include <vector>
#include "utils/ILogger.h"
#include "IApiClient.h"
#include "models/Country.h"

class CountryService {
public:
    explicit CountryService(ILogger& logger, IApiClient& apiClient) : _logger(logger), _apiClient(apiClient) {}

    [[nodiscard]] std::vector<Country> getCountries();

private:
    ILogger& _logger;
    IApiClient& _apiClient;
};

#endif // COUNTRY_SERVICE_H