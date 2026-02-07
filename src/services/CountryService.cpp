#include <string>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include "services/CountryService.h"
#include "utils/Cache.h"

using json = nlohmann::json;

static Cache<std::string, std::vector<Country>> cache;
const std::string cacheKey = "countries";

std::vector<Country> CountryService::getCountries() {

    if (auto cached = cache.get(cacheKey); cached.has_value()) {
        return cached.value();
    }

    std::string response = _apiClient.getAllCountries();
    _logger.log(ILogger::Level::DEBUG, "Response: " + response);

    std::vector<Country> countries;

    try {
        auto j = json::parse(response);
        if (j.contains("countries") && j["countries"].is_array()) {
            for (const auto& item : j["countries"]) {
                Country country;
                country.name = item.value("name_en", "");
                country.flag_url = item.value("flag_url_32", "");
                countries.push_back(country);
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }

    cache.put(cacheKey, countries, std::chrono::hours(1));

    return countries;
}
