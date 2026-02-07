#include <gtest/gtest.h>
#include "services/CountryService.h"
#include "FakeLogger.h"
#include "FakeApiClient.h"

TEST(CountryServiceTest, GetCountriesReturnData) {
    FakeLogger logger;
    FakeApiClient apiClient;
    CountryService service(logger, apiClient);
    std::vector<Country> result = service.getCountries();
    EXPECT_FALSE(result.empty());
}