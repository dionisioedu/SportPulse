#ifndef SPORT_SERVICE_H
#define SPORT_SERVICE_H

#include <vector>
#include "models/Sport.h"
#include "utils/ILogger.h"
#include "IApiClient.h"

class SportService
{
public:
    explicit SportService(ILogger& logger, IApiClient& apiClient) : _logger(logger), _apiClient(apiClient) {}

    [[nodiscard]] std::vector<Sport> getSports();

private:
    ILogger& _logger;
    IApiClient& _apiClient;
};

#endif // SPORT_SERVICE_H