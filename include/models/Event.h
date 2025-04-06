#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Event {
    Event();
    Event(const json& item) :
        idEvent(getString(item, "idEvent")),
        idAPIfootball(getString(item, "idAPIfootball")),
        strEvent(getString(item, "strEvent")),
        strEventAlternate(getString(item, "strEventAlternate")),
        strFilename(getString(item, "strFilename")),
        strSport(getString(item, "strSport")),
        idLeague(getString(item, "idLeague")),
        strLeague(getString(item, "strLeague")),
        strLeagueBadge(getString(item, "strLeagueBadge")),
        strSeason(getString(item, "strSeason")),
        strDescriptionEN(getString(item, "strDescriptionEN")),
        strHomeTeam(getString(item, "strHomeTeam")),
        strAwayTeam(getString(item, "strAwayTeam")),
        intHomeScore(getString(item, "intHomeScore")),
        intAwayScore(getString(item, "intAwayScore")),
        intRound(getString(item, "intRound")),
        intSpectators(getString(item, "intSpectators")),
        strOfficial(getString(item, "strOfficial")),
        strTimestamp(getString(item, "strTimestamp")),
        dateEvent(getString(item, "dateEvent")),
        dateEventLocal(getString(item, "dateEventLocal")),
        strTime(getString(item, "strTime")),
        strTimeLocal(getString(item, "strTimeLocal")),
        strGroup(getString(item, "strGroup")),
        idHomeTeam(getString(item, "idHomeTeam")),
        strHomeTeamBadge(getString(item, "strHomeTeamBadge")),
        idAwayTeam(getString(item, "idAwayTeam")),
        strAwayTeamBadge(getString(item, "strAwayTeamBadge")),
        intScore(getString(item, "intScore")),
        intScoreVotes(getString(item, "intScoreVotes")),
        strResult(getString(item, "strResult")),
        idVenue(getString(item, "idVenue")),
        strVenue(getString(item, "strVenue")),
        strCountry(getString(item, "strCountry")),
        strCity(getString(item, "strCity")),
        strPoster(getString(item, "strPoster")),
        strSquare(getString(item, "strSquare")),
        strFanart(getString(item, "strFanart")),
        strThumb(getString(item, "strThumb")),
        strBanner(getString(item, "strBanner")),
        strMap(getString(item, "strMap")),
        strTweet1(getString(item, "strTweet1")),
        strTweet2(getString(item, "strTweet2")),
        strTweet3(getString(item, "strTweet3")),
        strVideo(getString(item, "strVideo")),
        strStatus(getString(item, "strStatus")),
        strPostponed(getString(item, "strPostponed")),
        strLocked(getString(item, "strLocked"))
    {}

    std::string idEvent;
    std::string idAPIfootball;
    std::string strEvent;
    std::string strEventAlternate;
    std::string strFilename;
    std::string strSport;
    std::string idLeague;
    std::string strLeague;
    std::string strLeagueBadge;
    std::string strSeason;
    std::string strDescriptionEN;
    std::string strHomeTeam;
    std::string strAwayTeam;
    std::string intHomeScore;
    std::string intAwayScore;
    std::string intRound;
    std::string intSpectators;
    std::string strOfficial;
    std::string strTimestamp;
    std::string dateEvent;
    std::string dateEventLocal;
    std::string strTime;
    std::string strTimeLocal;
    std::string strGroup;
    std::string idHomeTeam;
    std::string strHomeTeamBadge;
    std::string idAwayTeam;
    std::string strAwayTeamBadge;
    std::string intScore;
    std::string intScoreVotes;
    std::string strResult;
    std::string idVenue;
    std::string strVenue;
    std::string strCountry;
    std::string strCity;
    std::string strPoster;
    std::string strSquare;
    std::string strFanart;
    std::string strThumb;
    std::string strBanner;
    std::string strMap;
    std::string strTweet1;
    std::string strTweet2;
    std::string strTweet3;
    std::string strVideo;
    std::string strStatus;
    std::string strPostponed;
    std::string strLocked;

private:
    inline std::string getString(const json& item, const std::string& key) {
        return item.contains(key) && !item[key].is_null() ? item[key].get<std::string>() : "";
    }
};

#endif // EVENT_H