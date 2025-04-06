#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Player {
    Player();
    Player(const json& item) {
        idPlayer = getString(item, "idPlayer");
        idTeam = getString(item, "idTeam");
        strPlayer = getString(item, "strPlayer");
        strTeam = getString(item, "strTeam");
        strSport = getString(item, "strSport");
        strThumb = getString(item, "strThumb");
        strCutout = getString(item, "strCutout");
        strNationality = getString(item, "strNationality");
        dateBorn = getString(item, "dateBorn");
        strStatus = getString(item, "strStatus");
        strGender = getString(item, "strGender");
        strPosition = getString(item, "strPosition");
        relevance = getString(item, "relevance");
    };

    std::string idPlayer;
    std::string idTeam;
    std::string strPlayer;
    std::string strTeam;
    std::string strSport;
    std::string strThumb;
    std::string strCutout;
    std::string strNationality;
    std::string dateBorn;
    std::string strStatus;
    std::string strGender;
    std::string strPosition;
    std::string relevance;

private:
    inline std::string getString(const json& item, const std::string& key) {
        return item.contains(key) && !item[key].is_null() ? item[key].get<std::string>() : "";
    }
};

#endif // PLAYER_H