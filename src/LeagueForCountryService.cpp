#include "LeagueForCountryService.h"
#include "ApiClient.h"
#include "Cache.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static Cache<std::string, std::vector<LeagueForCountry>> cache;
const std::string cacheKey = "league_for_country_";

inline std::string getString(const json& item, const std::string& key) {
    return item.contains(key) && !item[key].is_null() ? item[key].get<std::string>() : "";
}

std::vector<LeagueForCountry> LeagueForCountryService::getAllLeaguesForCountry(const std::string country, const std::string sport) {

    if (auto cached = cache.get(cacheKey + country + sport); cached.has_value()) {
        return cached.value();
    }

    ApiClient client;
    std::string response;
    
    if (sport == "") {
        response = client.getLeaguesForCountry(country);
    } else {
        response = client.getLeaguesForCountry(country, sport);
    }

    _logger.log(ILogger::Level::DEBUG, "Response: " + response);

    std::vector<LeagueForCountry> leagues;

    try {
        auto j = json::parse(response);
        if (j.contains("countries") && j["countries"].is_array()) {

            for (const auto& item : j["countries"]) {
                LeagueForCountry league;
                league.idLeague = getString(item, "idLeague");
                league.idSoccerXML = getString(item, "idSoccerXML");
                league.idAPIfootball = getString(item, "idAPIfootball");
                league.strSport = getString(item, "strSport");
                league.strLeague = getString(item, "strLeague");
                league.strLeagueAlternate = getString(item, "strLeagueAlternate");
                league.intDivision = getString(item, "intDivision");
                league.idCup = getString(item, "idCup");
                league.strCurrentSeason = getString(item, "strCurrentSeason");
                league.intFormedYear = getString(item, "intFormedYear");
                league.dateFirstEvent = getString(item, "dateFirstEvent");
                league.strGender = getString(item, "strGender");
                league.strCountry = getString(item, "strCountry");
                league.strWebsite = getString(item, "strWebsite");
                league.strFacebook = getString(item, "strFacebook");
                league.strInstagram = getString(item, "strInstagram");
                league.strTwitter = getString(item, "strTwitter");
                league.strYoutube = getString(item, "strYoutube");
                league.strRSS = getString(item, "strRSS");
                league.strDescriptionEN = getString(item, "strDescriptionEN");
                league.strDescriptionDE = getString(item, "strDescriptionDE");
                league.strDescriptionFR = getString(item, "strDescriptionFR");
                league.strDescriptionIT = getString(item, "strDescriptionIT");
                league.strDescriptionCN = getString(item, "strDescriptionCN");
                league.strDescriptionJP = getString(item, "strDescriptionJP");
                league.strDescriptionRU = getString(item, "strDescriptionRU");
                league.strDescriptionES = getString(item, "strDescriptionES");
                league.strDescriptionPT = getString(item, "strDescriptionPT");
                league.strDescriptionSE = getString(item, "strDescriptionSE");
                league.strDescriptionNL = getString(item, "strDescriptionNL");
                league.strDescriptionHU = getString(item, "strDescriptionHU");
                league.strDescriptionNO = getString(item, "strDescriptionNO");
                league.strDescriptionPL = getString(item, "strDescriptionPL");
                league.strDescriptionIL = getString(item, "strDescriptionIL");
                league.strTvRights = getString(item, "strTvRights");
                league.strFanart1 = getString(item, "strFanart1");
                league.strFanart2 = getString(item, "strFanart2");
                league.strFanart3 = getString(item, "strFanart3");
                league.strFanart4 = getString(item, "strFanart4");
                league.strBanner = getString(item, "strBanner");
                league.strBadge = getString(item, "strBadge");
                league.strLogo = getString(item, "strLogo");
                league.strPoster = getString(item, "strPoster");
                league.strTrophy = getString(item, "strTrophy");
                league.strNaming = getString(item, "strNaming");
                league.strComplete = getString(item, "strComplete");
                league.strLocked = getString(item, "strLocked");
                leagues.push_back(league);
            }
        }
    } catch (std::exception& e) {
        std::string error_message(e.what());
        _logger.log(ILogger::Level::ERROR, error_message);
    }

    cache.put(cacheKey + country + sport, leagues, std::chrono::hours(1));

    return leagues;
}