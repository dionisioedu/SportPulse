#ifndef IAPI_CLIENT_H
#define IAPI_CLIENT_H

class IApiClient {
public:
    [[nodiscard]] virtual std::string searchTeams(const std::string teamName) = 0;
    [[nodiscard]] virtual std::string searchTeamsByShortCode(const std::string shortCode) = 0;
    [[nodiscard]] virtual std::string searchPlayers(const std::string playerName) = 0;
    [[nodiscard]] virtual std::string searchPlayersFromTeam(const std::string teamName) = 0;
    [[nodiscard]] virtual std::string searchEventByName(const std::string eventName) = 0;
    [[nodiscard]] virtual std::string searchEventsByNameAndYear(const std::string eventName, const std::string startYear, const std::string endYear) = 0;
    [[nodiscard]] virtual std::string searchEventByEventFileName(const std::string eventFileName) = 0;
    [[nodiscard]] virtual std::string searchForVenue(const std::string venueName) = 0;

    [[nodiscard]] virtual std::string getAllSports() = 0;
    [[nodiscard]] virtual std::string getAllLeagues() = 0;
    [[nodiscard]] virtual std::string getAllCountries() = 0;
    [[nodiscard]] virtual std::string getLeaguesForCountry(const std::string country) = 0;
    [[nodiscard]] virtual std::string getLeaguesForCountry(const std::string country, const std::string sport) = 0;

    [[nodiscard]] virtual std::string fetchLiveScores() = 0;
};

#endif // IAPI_CLIENT_H