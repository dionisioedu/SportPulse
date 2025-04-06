#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

inline std::string getString(const json& item, const std::string& key) {
    return item.contains(key) && !item[key].is_null() ? item[key].get<std::string>() : "";
}

struct Team {
    Team();
    Team(const json& item) {
        idTeam = getString(item, "idTeam");
        idESPN = getString(item, "idESPN");
        idAPIfootball = getString(item, "idAPIfootball");
        intLoved = getString(item, "intLoved");
        strTeam = getString(item, "strTeam");
        strTeamAlternate = getString(item, "strTeamAlternate");
        strTeamShort = getString(item, "strTeamShort");
        intFormedYear = getString(item, "intFormedYear");
        strSport = getString(item, "strSport");
        strLeague = getString(item, "strLeague");
        idLeague = getString(item, "idLeague");
        strLeague2 = getString(item, "strLeague2");
        idLeague2 = getString(item, "idLeague2");
        strLeague3 = getString(item, "strLeague3");
        idLeague3 = getString(item, "idLeague3");
        strLeague4 = getString(item, "strLeague4");
        idLeague4 = getString(item, "idLeague4");
        strLeague5 = getString(item, "strLeague5");
        idLeague5 = getString(item, "idLeague5");
        strLeague6 = getString(item, "strLeague6");
        idLeague6 = getString(item, "idLeague6");
        strLeague7 = getString(item, "strLeague7");
        idLeague7 = getString(item, "idLeague7");
        strDivision = getString(item, "strDivision");
        idVenue = getString(item, "idVenue");
        strStadium = getString(item, "strStadium");
        strKeywords = getString(item, "strKeywords");
        strRSS = getString(item, "strRSS");
        strLocation = getString(item, "strLocation");
        intStadiumCapacity = getString(item, "intStadiumCapacity");
        strWebsite = getString(item, "strWebsite");
        strFacebook = getString(item, "strFacebook");
        strTwitter = getString(item, "strTwitter");
        strInstagram = getString(item, "strInstagram");
        strDescriptionEN = getString(item, "strDescriptionEN");
        strDescriptionDE = getString(item, "strDescriptionDE");
        strDescriptionFR = getString(item, "strDescriptionFR");
        strDescriptionCN = getString(item, "strDescriptionCN");
        strDescriptionIT = getString(item, "strDescriptionIT");
        strDescriptionJP = getString(item, "strDescriptionJP");
        strDescriptionRU = getString(item, "strDescriptionRU");
        strDescriptionES = getString(item, "strDescriptionES");
        strDescriptionPT = getString(item, "strDescriptionPT");
        strDescriptionSE = getString(item, "strDescriptionSE");
        strDescriptionNL = getString(item, "strDescriptionNL");
        strDescriptionHU = getString(item, "strDescriptionHU");
        strDescriptionNO = getString(item, "strDescriptionNO");
        strDescriptionIL = getString(item, "strDescriptionIL");
        strDescriptionPL = getString(item, "strDescriptionPL");
        strColour1 = getString(item, "strColour1");
        strColour2 = getString(item, "strColour2");
        strColour3 = getString(item, "strColour3");
        strGender = getString(item, "strGender");
        strCountry = getString(item, "strCountry");
        strBadge = getString(item, "strBadge");
        strLogo = getString(item, "strLogo");
        strFanart1 = getString(item, "strFanart1");
        strFanart2 = getString(item, "strFanart2");
        strFanart3 = getString(item, "strFanart3");
        strFanart4 = getString(item, "strFanart4");
        strBanner = getString(item, "strBanner");
        strEquipment = getString(item, "strEquipment");
        strYoutube = getString(item, "strYoutube");
        strLocked = getString(item, "strLocked");
    }

    std::string idTeam;
    std::string idESPN;
    std::string idAPIfootball;
    std::string intLoved;
    std::string strTeam;
    std::string strTeamAlternate;
    std::string strTeamShort;
    std::string intFormedYear;
    std::string strSport;
    std::string strLeague;
    std::string idLeague;
    std::string strLeague2;
    std::string idLeague2;
    std::string strLeague3;
    std::string idLeague3;
    std::string strLeague4;
    std::string idLeague4;
    std::string strLeague5;
    std::string idLeague5;
    std::string strLeague6;
    std::string idLeague6;
    std::string strLeague7;
    std::string idLeague7;
    std::string strDivision;
    std::string idVenue;
    std::string strStadium;
    std::string strKeywords;
    std::string strRSS;
    std::string strLocation;
    std::string intStadiumCapacity;
    std::string strWebsite;
    std::string strFacebook;
    std::string strTwitter;
    std::string strInstagram;
    std::string strDescriptionEN;
    std::string strDescriptionDE;
    std::string strDescriptionFR;
    std::string strDescriptionCN;
    std::string strDescriptionIT;
    std::string strDescriptionJP;
    std::string strDescriptionRU;
    std::string strDescriptionES;
    std::string strDescriptionPT;
    std::string strDescriptionSE;
    std::string strDescriptionNL;
    std::string strDescriptionHU;
    std::string strDescriptionNO;
    std::string strDescriptionIL;
    std::string strDescriptionPL;
    std::string strColour1;
    std::string strColour2;
    std::string strColour3;
    std::string strGender;
    std::string strCountry;
    std::string strBadge;
    std::string strLogo;
    std::string strFanart1;
    std::string strFanart2;
    std::string strFanart3;
    std::string strFanart4;
    std::string strBanner;
    std::string strEquipment;
    std::string strYoutube;
    std::string strLocked;
};

struct TeamsData {
    std::vector<Team> teams;
};

#endif // TEAM_H