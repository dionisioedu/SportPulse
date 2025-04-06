#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>

struct Team {
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