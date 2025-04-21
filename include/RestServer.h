#ifndef REST_SERVER_H
#define REST_SERVER_H

#include <cpprest/http_listener.h>
#include "services/LeagueService.h"
#include "services/SportService.h"
#include "services/CountryService.h"
#include "services/SearchService.h"
#include "utils/ILogger.h"

class RestServer {
public:
    RestServer(
        const std::string& address,
        LeagueService& leagueService,
        SportService& sportService,
        CountryService& countryService,
        SearchService& searchService,
        ILogger& logger);

    void start();
    void stop();

private:
    void handleGetLeagues(web::http::http_request request);
    void handleGetSports(web::http::http_request request);
    void handleGetCountries(web::http::http_request request);
    void handleGetLeaguesForCountry(web::http::http_request request);
    void handleGetLeague(web::http::http_request request);

    void handleSearchTeamsByName(web::http::http_request request);
    void handleSearchTeamsByShortCode(web::http::http_request request);
    void handleSearchPlayers(web::http::http_request request);
    void handleSearchPlayersFromTeam(web::http::http_request request);
    void handleSearchEventByName(web::http::http_request request);
    void handleSearchEventsByNameAndYear(web::http::http_request request);
    void handleSearchEventByEventFileName(web::http::http_request request);
    void handleSearchForVenue(web::http::http_request request);

    web::http::experimental::listener::http_listener _listener;
    LeagueService& _leagueService;
    SportService& _sportService;
    CountryService& _countryService;
    SearchService& _searchService;
    ILogger& _logger;
};

#endif // REST_SERVER_H