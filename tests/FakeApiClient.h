#include "IApiClient.h"

class FakeApiClient : public IApiClient {
public:
    std::string searchTeams(const std::string teamName) override {
        return R"({"teams":[{"idTeam":"133604","idSoccerXML":"133604","idAPIfootball":"133604","strTeam":"Manchester United","strTeamShort":"MUN","strAlternatenateTeam":"Manchester Utd","intFormedYear":"1878","strSport":"Soccer","strLeague":"English Premier League","idLeague":"4328","strLeague2":"UEFA Champions League","idLeague2":"4480","strLeague3":"","idLeague3":"","strLeague4":"","idLeague4":"","strLeague5":"","idLeague5":"","strLeague6":"","idLeague6":"","strLeague7":"","idLeague7":"","strDivision":"1","idVenue":"133604","strStadium":"Old Trafford","strKeywords":"Red Devils,Theatre of Dreams","strRSS":"https://www.thesportsdb.com/rss/133604.xml","strLocation":"Manchester, England","intStadiumCapacity":"76212","strWebsite":"www.manutd.com","strFacebook":"www.facebook.com/manchesterunited","strTwitter":"www.twitter.com/manutd","strInstagram":"www.instagram.com/manchesterunited","strDescriptionEN":"Manchester United Football Club is a professional football club based in Old Trafford, Greater Manchester, England. Founded in 1878 as Newton Heath LYR Football Club, the team changed its name to Manchester United in 1902 and moved to its current stadium, Old Trafford, in 1910.","strColour1":"#DA291C","strColour2":"#FFFFFF","strColour3":"#000000","strGender":"Male","strCountry":"England","strBadge":"https://www.thesportsdb.com/images/media/team/badge/vrtrtp1448813175.png","strLogo":"https://www.thesportsdb.com/images/media/team/logo/vrtrtp1448813175.png","strFanart1":"https://www.thesportsdb.com/images/media/team/fanart/vrtrtp1448813175.jpg","strFanart2":"https://www.thesportsdb.com/images/media/team/fanart/vrtrtp1448813175.jpg","strFanart3":"https://www.thesportsdb.com/images/media/team/fanart/vrtrtp1448813175.jpg","strFanart4":"https://www.thesportsdb.com/images/media/team/fanart/vrtrtp1448813175.jpg","strBanner":"https://www.thesportsdb.com/images/media/team/banner/vrtrtp1448813175.jpg","strEquipment":"","strYoutube":"www.youtube.com/manchesterunitedtv","strLocked":"unlocked"  }]})";
    }

    std::string searchTeamsByShortCode(const std::string shortCode) override {
        return R"({"teams":[]})";
    }

    std::string searchPlayers(const std::string playerName) override {
        return R"({"player":[]})";
    }

    std::string searchPlayersFromTeam(const std::string teamName) override {
        return R"({"player":[]})";
    }

    std::string searchEventByName(const std::string eventName) override {
        return R"({"event":[]})";
    }

    std::string searchEventsByNameAndYear(const std::string eventName, const std::string startYear, const std::string endYear) override {
        return R"({"event":[]})";
    }

    std::string searchEventByEventFileName(const std::string eventFileName) override {
        return R"({"event":[]})";
    }

    std::string searchForVenue(const std::string venueName) override {
        return R"({"venues":[]})";
    }

    std::string getAllSports() override {
        return R"({"sports":[{"idSport":"1","strSport":"Soccer","strFormat":"TeamvsTeam","strSportThumb":"https://www.thesportsdb.com/images/sports/soccer.jpg","strSportThumbBW":"https://www.thesportsdb.com/images/sports/soccer_bw.jpg","strSportDescription":"Soccer, also known as football, is a team sport played between two teams of eleven players with a spherical ball. It is the most popular sport in the world and is played by over 250 million players in over 200 countries."}]})";
    }

    std::string getAllLeagues() override {
        return R"({"leagues":[{"idLeague":"1","strLeague":"English Premier League","strSport":"Soccer","strLeagueAlternate":"EPL"}]})";
    }

    std::string getAllCountries() override {
        return R"({"countries":[{"name_en":"Brazil","flag_url_32":"https://www.thesportsdb.com/images/flags/brazil.png"}]})";
    }

    std::string getLeaguesForCountry(const std::string country) override {
        return R"({"countries":[]})";
    }

    std::string getLeaguesForCountry(const std::string country, const std::string sport) override {
        return R"({"countries":[]})";
    }

    std::string getSeasonsFromLeague(const std::string leagueId) override {
        return R"({"seasons":[]})";
    }

    std::string getLeague(const std::string leagueId) override {
        return R"({"leagues":[]})";
    }

    std::string fetchLiveScores() override {
        return R"({"events":[]})";
    }

};