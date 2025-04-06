#include <nlohmann/json.hpp>
#include "services/SearchService.h"
#include "utils/Cache.h"

using json = nlohmann::json;

static Cache<std::string, std::vector<Team>> cache;

inline std::string getString(const json& item, const std::string& key) {
    return item.contains(key) && !item[key].is_null() ? item[key].get<std::string>() : "";
}

std::vector<Team> SearchService::searchTeamsByName(const std::string teamName) {

    if (auto cached = cache.get(teamName); cached.has_value()) {
        return cached.value();
    }

    log.log(ILogger::Level::DEBUG, "SearchService requesting ApiClient for searchTeams: " + teamName);

    std::string response = apiClient.searchTeams(teamName);
    log.log(ILogger::Level::DEBUG, "Response: " + response);

    std::vector<Team> teams;
    try {
        auto j = json::parse(response);
        if (j.contains("teams") && j["teams"].is_array()) {
            for (const auto& item : j["teams"]) {
                Team team;
                team.idTeam = getString(item, "idTeam");
                team.idESPN = getString(item, "idESPN");
                team.idAPIfootball = getString(item, "idAPIfootball");
                team.intLoved = getString(item, "intLoved");
                team.strTeam = getString(item, "strTeam");
                team.strTeamAlternate = getString(item, "strTeamAlternate");
                team.strTeamShort = getString(item, "strTeamShort");
                team.intFormedYear = getString(item, "intFormedYear");
                team.strSport = getString(item, "strSport");
                team.strLeague = getString(item, "strLeague");
                team.idLeague = getString(item, "idLeague");
                team.strLeague2 = getString(item, "strLeague2");
                team.idLeague2 = getString(item, "idLeague2");
                team.strLeague3 = getString(item, "strLeague3");
                team.idLeague3 = getString(item, "idLeague3");
                team.strLeague4 = getString(item, "strLeague4");
                team.idLeague4 = getString(item, "idLeague4");
                team.strLeague5 = getString(item, "strLeague5");
                team.idLeague5 = getString(item, "idLeague5");
                team.strLeague6 = getString(item, "strLeague6");
                team.idLeague6 = getString(item, "idLeague6");
                team.strLeague7 = getString(item, "strLeague7");
                team.idLeague7 = getString(item, "idLeague7");
                team.strDivision = getString(item, "strDivision");
                team.idVenue = getString(item, "idVenue");
                team.strStadium = getString(item, "strStadium");
                team.strKeywords = getString(item, "strKeywords");
                team.strRSS = getString(item, "strRSS");
                team.strLocation = getString(item, "strLocation");
                team.intStadiumCapacity = getString(item, "intStadiumCapacity");
                team.strWebsite = getString(item, "strWebsite");
                team.strFacebook = getString(item, "strFacebook");
                team.strTwitter = getString(item, "strTwitter");
                team.strInstagram = getString(item, "strInstagram");
                team.strDescriptionEN = getString(item, "strDescriptionEN");
                team.strDescriptionDE = getString(item, "strDescriptionDE");
                team.strDescriptionFR = getString(item, "strDescriptionFR");
                team.strDescriptionCN = getString(item, "strDescriptionCN");
                team.strDescriptionIT = getString(item, "strDescriptionIT");
                team.strDescriptionJP = getString(item, "strDescriptionJP");
                team.strDescriptionRU = getString(item, "strDescriptionRU");
                team.strDescriptionES = getString(item, "strDescriptionES");
                team.strDescriptionPT = getString(item, "strDescriptionPT");
                team.strDescriptionSE = getString(item, "strDescriptionSE");
                team.strDescriptionNL = getString(item, "strDescriptionNL");
                team.strDescriptionHU = getString(item, "strDescriptionHU");
                team.strDescriptionNO = getString(item, "strDescriptionNO");
                team.strDescriptionIL = getString(item, "strDescriptionIL");
                team.strDescriptionPL = getString(item, "strDescriptionPL");
                team.strColour1 = getString(item, "strColour1");
                team.strColour2 = getString(item, "strColour2");
                team.strColour3 = getString(item, "strColour3");
                team.strGender = getString(item, "strGender");
                team.strCountry = getString(item, "strCountry");
                team.strBadge = getString(item, "strBadge");
                team.strLogo = getString(item, "strLogo");
                team.strFanart1 = getString(item, "strFanart1");
                team.strFanart2 = getString(item, "strFanart2");
                team.strFanart3 = getString(item, "strFanart3");
                team.strFanart4 = getString(item, "strFanart4");
                team.strBanner = getString(item, "strBanner");
                team.strEquipment = getString(item, "strEquipment");
                team.strYoutube = getString(item, "strYoutube");
                team.strLocked = getString(item, "strLocked");
                teams.push_back(team);
            }
        }
    } catch (std::exception& e) {
        std::string error_message("Error parsin JSON: " + std::string(e.what()));
        log.log(ILogger::Level::ERROR, error_message);
    }

    cache.put(teamName, teams, std::chrono::hours(1));

    return teams;
}