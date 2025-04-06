#ifndef VENUE_H
#define VENUE_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Venue {
    Venue();
    Venue(const json& item) {
        idVenue = getString(item, "idVenue");
        idDupe = getString(item, "idDupe");
        strVenue = getString(item, "strVenue");
        strVenueAlternate = getString(item, "strVenueAlternate");
        strVenueSponsor = getString(item, "strVenueSponsor");
        strSport = getString(item, "strSport");
        strDescriptionEN = getString(item, "strDescriptionEN");
        strArchitect = getString(item, "strArchitect");
        intCapacity = getString(item, "intCapacity");
        strCost = getString(item, "strCost");
        strCountry = getString(item, "strCountry");
        strLocation = getString(item, "strLocation");
        strTimezone = getString(item, "strTimezone");
        intFormedYear = getString(item, "intFormedYear");
        strFanart1 = getString(item, "strFanart1");
        strFanart2 = getString(item, "strFanart2");
        strFanart3 = getString(item, "strFanart3");
        strFanart4 = getString(item, "strFanart4");
        strThumb = getString(item, "strThumb");
        strLogo = getString(item, "strLogo");
        strMap = getString(item, "strMap");
        strWebsite = getString(item, "strWebsite");
        strFacebook = getString(item, "strFacebook");
        strInstagram = getString(item, "strInstagram");
        strTwitter = getString(item, "strTwitter");
        strYoutube = getString(item, "strYoutube");
        strLocked = getString(item, "strLocked");
    }

    std::string idVenue;
    std::string idDupe;
    std::string strVenue;
    std::string strVenueAlternate;
    std::string strVenueSponsor;
    std::string strSport;
    std::string strDescriptionEN;
    std::string strArchitect;
    std::string intCapacity;
    std::string strCost;
    std::string strCountry;
    std::string strLocation;
    std::string strTimezone;
    std::string intFormedYear;
    std::string strFanart1;
    std::string strFanart2;
    std::string strFanart3;
    std::string strFanart4;
    std::string strThumb;
    std::string strLogo;
    std::string strMap;
    std::string strWebsite;
    std::string strFacebook;
    std::string strInstagram;
    std::string strTwitter;
    std::string strYoutube;
    std::string strLocked;

private:
    inline std::string getString(const json& item, const std::string& key) {
        return item.contains(key) && !item[key].is_null() ? item[key].get<std::string>() : "";
    }
};

#endif // VENUE_H