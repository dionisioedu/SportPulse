#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "services/LeagueService.h"
#include "ApiClient.h"
#include "utils/Cache.h"

using json = nlohmann::json;

static Cache<std::string, std::vector<League>> cache;
const std::string cacheKey = "leagues";

std::vector<League> LeagueService::getLeagues() {

    if (auto cached = cache.get(cacheKey); cached.has_value()) {
        return cached.value();
    }

    ApiClient client;
    std::string response = client.getAllLeagues();
    _logger.log(ILogger::Level::DEBUG, "Response: " + response);

    std::vector<League> leagues;

    try {
        auto j = json::parse(response);
        if (j.contains("leagues") && j["leagues"].is_array()) {
            for (const auto& item : j["leagues"]) {
                League league;
                league.idLeague = item.value("idLeague", "");
                league.strLeague = item.value("strLeague", "");
                league.strSport = item.value("strSport", "");
                league.strLeagueAlternate = item.value("strLeagueAlternate", "");
                leagues.push_back(league);
            }
        }
    } catch (const std::exception& e) {
        std::string error_message(e.what());
        _logger.log(ILogger::Level::ERROR, error_message);
    }

    cache.put(cacheKey, leagues, std::chrono::hours(1));

    return leagues;
}
