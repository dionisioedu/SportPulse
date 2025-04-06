#include <gtest/gtest.h>
#include "services/CountryService.h"

class FakeLogger : public ILogger {
public:
    std::vector<std::string> logs;

    void log(Level level, const std::string& message) override {}
};

TEST(CountryServiceTest, GetCountriesReturnData) {
    FakeLogger logger;
    CountryService service(logger);
    std::vector<Country> result = service.getCountries();
    EXPECT_FALSE(result.empty());
}