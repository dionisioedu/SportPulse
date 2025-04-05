#include "RestServer.h"
#include <cpprest/json.h>
#include "nlohmann/json.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

RestServer::RestServer(
    const std::string& address,
    LeagueService& leagueService,
    SportService& sportService,
    CountryService& countryService,
    LeagueForCountryService& leagueForCountryService,
    ILogger& logger)
    : _leagueService(leagueService),
      _sportService(sportService),
      _countryService(countryService),
      _leagueForCountryService(leagueForCountryService),
      _logger(logger) {

    _listener = http_listener(utility::conversions::to_string_t(address));
    _listener.support(methods::GET, [this](http_request request) {
        auto path = uri::split_path(uri::decode(request.request_uri().path()));
        if (path.empty()) {
            request.reply(status_codes::NotFound);
            return;
        }

        if (path[0] == U("leagues")) {
            handle_get_leagues(request);
        } else if (path[0] == U("sports")) {
            handle_get_sports(request);
        } else if (path[0] == U("countries")) {
            handle_get_countries(request);
        } else if (path[0] == U("leaguesForCountry")) {
            handle_get_leagues_for_country(request);
        } else {
            request.reply(status_codes::NotFound);
        }
    });
}

void RestServer::start() {
    _listener
        .open()
        .then([this](){ _logger.log(ILogger::Level::INFO, "Starting REST server at: " + _listener.uri().to_string()); })
        .wait();
}

void RestServer::stop() {
    _listener
        .close()
        .then([this](){ _logger.log(ILogger::Level::INFO, "Stopping REST server."); })
        .wait();
}

void RestServer::handle_get_leagues(web::http::http_request request) {
    _logger.log(ILogger::Level::INFO, "Received GET request for leagues.");

    auto leagues = _leagueService.getLeagues();
    
    json::value jArray = json::value::array();
    for (size_t i = 0; i < leagues.size(); ++i) {
        json::value jLeague;
        jLeague[U("idLeague")] = json::value::string(utility::conversions::to_string_t(leagues[i].idLeague));
        jLeague[U("strLeague")] = json::value::string(utility::conversions::to_string_t(leagues[i].strLeague));
        jLeague[U("strSport")] = json::value::string(utility::conversions::to_string_t(leagues[i].strSport));
        jLeague[U("strLeagueAlternate")] = json::value::string(utility::conversions::to_string_t(leagues[i].strLeagueAlternate));
        jArray[i] = jLeague;
    }

    request.reply(status_codes::OK, jArray);
    _logger.log(ILogger::Level::INFO, "Sending response with leagues.");
    _logger.log(ILogger::Level::DEBUG, "Leagues: " + jArray.serialize());
}

void RestServer::handle_get_sports(web::http::http_request request) {
    auto sports = _sportService.getSports();

    json::value jArray = json::value::array();
    for (size_t i = 0; i < sports.size(); ++i) {
        json::value jSport;
        jSport[U("idSport")] = json::value::string(utility::conversions::to_string_t(sports[i].idSport));
        jSport[U("strSport")] = json::value::string(utility::conversions::to_string_t(sports[i].strSport));

        jArray[i] = jSport;
    }
    request.reply(status_codes::OK, jArray);
}

void RestServer::handle_get_countries(web::http::http_request request) {
    auto countries = _countryService.getCountries();

    json::value jArray = json::value::array();
    for (size_t i = 0; i < countries.size(); ++i) {
        json::value jCountry;
        jCountry[U("name")] = json::value::string(utility::conversions::to_string_t(countries[i].name));
        jCountry[U("flag_url")] = json::value::string(utility::conversions::to_string_t(countries[i].flag_url));
        jArray[i] = jCountry;
    }
    request.reply(status_codes::OK, jArray);
}

void RestServer::handle_get_leagues_for_country(web::http::http_request request) {
    auto queries = uri::split_query(request.relative_uri().query());
    std::string country;
    std::string sport;
    if (queries.find(U("country")) != queries.end()) {
        country = utility::conversions::to_utf8string(queries[U("country")]);
    }
    if (queries.find(U("sport")) != queries.end()) {
        sport = utility::conversions::to_utf8string(queries[U("sport")]);
    }

    auto leagues = _leagueForCountryService.getAllLeaguesForCountry(country, sport);
    
    json::value jArray = json::value::array();
    for (size_t i = 0; i < leagues.size(); ++i) {
        json::value jLeague;
        jLeague[U("idLeague")] = json::value::string(utility::conversions::to_string_t(leagues[i].idLeague));
        jLeague[U("strLeague")] = json::value::string(utility::conversions::to_string_t(leagues[i].strLeague));
        jArray[i] = jLeague;
    }
    request.reply(status_codes::OK, jArray);
}
