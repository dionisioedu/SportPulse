#ifndef REST_SERVER_H
#define REST_SERVER_H

#include <cpprest/http_listener.h>
#include "services/LeagueService.h"
#include "services/SportService.h"
#include "services/CountryService.h"
#include "services/LeagueForCountryService.h"
#include "services/SearchService.h"
#include "utils/ILogger.h"

class RestServer {
public:
    RestServer(
        const std::string& address,
        LeagueService& leagueService,
        SportService& sportService,
        CountryService& countryService,
        LeagueForCountryService& leagueForCountryService,
        SearchService& searchService,
        ILogger& logger);

    void start();
    void stop();

private:
    void handle_get_leagues(web::http::http_request request);
    void handle_get_sports(web::http::http_request request);
    void handle_get_countries(web::http::http_request request);
    void handle_get_leagues_for_country(web::http::http_request request);

    web::http::experimental::listener::http_listener _listener;
    LeagueService& _leagueService;
    SportService& _sportService;
    CountryService& _countryService;
    LeagueForCountryService& _leagueForCountryService;
    SearchService& _searchService;
    ILogger& _logger;
};

#endif // REST_SERVER_H