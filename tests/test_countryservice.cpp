#include <gtest/gtest.h>
#include "services/CountryService.h"
#include "FakeLogger.h"

TEST(CountryServiceTest, GetCountriesReturnData) {
    FakeLogger logger;
    CountryService service(logger);
    std::vector<Country> result = service.getCountries();
    EXPECT_FALSE(result.empty());
}