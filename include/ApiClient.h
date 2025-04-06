#ifndef API_CLIENT_H
#define API_CLIENT_H

#include <string>
#include <vector>
#include "IApiClient.h"

class ApiClient : public IApiClient {
private:
    const std::string apiUrl = "https://www.thesportsdb.com/api/v1/json/3/";

    [[nodiscard]] std::string request(const std::string endpoint);

public:
    std::string searchTeams(const std::string teamName) override;
    std::string searchTeamsByShortCode(const std::string shortCode) override;
    std::string searchPlayers(const std::string playerName) override;
    std::string searchPlayersFromTeam(const std::string teamName) override;
    std::string searchEventByName(const std::string eventName) override;
    std::string searchEventsByNameAndYear(const std::string eventName, const std::string startYear, const std::string endYear) override;
    std::string searchEventByEventFileName(const std::string eventFileName) override;
    std::string searchForVenue(const std::string venueName) override;

    std::string getAllSports() override;
    std::string getAllLeagues() override;
    std::string getAllCountries() override;
    std::string getLeaguesForCountry(const std::string country) override;
    std::string getLeaguesForCountry(const std::string country, const std::string sport) override;

    std::string fetchLiveScores() override;
};

#endif // API_CLIENT_H