#include "SportService.h"
#include "ApiClient.h"
#include "Cache.h"
#include "Logger.h"
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <iostream>

using json = nlohmann::json;

static Cache<std::string, std::vector<Sport>> cache;
const std::string cacheKey = "sports";

std::vector<Sport> SportService::getSports() {

    if (auto cached = cache.get(cacheKey); cached.has_value()) {
        return cached.value();
    }

    ApiClient client;
    std::string response = client.getAllSports();
    logger_.log(Logger::Level::DEBUG, "Response: " + response);

    nlohmann::json json = nlohmann::json::parse(response);
    std::vector<Sport> sports;

    try {
        auto j = json::parse(response);
        if (j.contains("sports") && j["sports"].is_array()) {
            for (const auto& item : j["sports"]) {
                Sport sport;
                sport.idSport = item.value("idSport", "");
                sport.strSport = item.value("strSport", "");
                sport.strFormat = item.value("strFormat", "");
                sport.strSportThumb = item.value("strSportThumb", "");
                sport.strSportThumbBW = item.value("strSportThumbBW", "");
                sport.strSportDescription = item.value("strSportDescription", "");
                sport.strSportIconGreen = item.value("strSportIconGreen", "");
                sports.push_back(sport);
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
    }

    cache.put(cacheKey, sports, std::chrono::hours(1));

    return sports;
}
