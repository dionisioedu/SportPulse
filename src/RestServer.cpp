#include "RestServer.h"
#include <cpprest/json.h>
#include "nlohmann/json.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

namespace {
    void addCORSHeaders(http_response& response) {
        response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
        response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS"));
        response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
    }
}

RestServer::RestServer(
    const std::string& address,
    LeagueService& leagueService,
    SportService& sportService,
    CountryService& countryService,
    LeagueForCountryService& leagueForCountryService,
    SearchService& searchService,
    ILogger& logger)
    : _leagueService(leagueService),
      _sportService(sportService),
      _countryService(countryService),
      _leagueForCountryService(leagueForCountryService),
      _searchService(searchService),
      _logger(logger) {

    _listener = http_listener(utility::conversions::to_string_t(address));
    _listener.support(methods::GET, [this](http_request request) {
        auto path = uri::split_path(uri::decode(request.request_uri().path()));
        if (path.empty() || path[0] == U("api") || (path.size() == 1 && (path[0].empty() || path[0] == U("api")))) {
            // If GET / is requested, return a simple HTML page
            http_response response(status_codes::OK);
            response.headers().add(U("Content-Type"), U("text/html"));
            std::string htmlContent = "<!DOCTYPE html>"
                                      "<html>"
                                      "<head><title>SportPulse</title></head>"
                                      "<body>"
                                      "<h1>Welcome to SportPulse API</h1>"
                                      "<p>This is a backend service exposing a REST API for SportPulse.</p>"
                                      "</body>"
                                      "</html>";
            response.set_body(utility::conversions::to_string_t(htmlContent));
            request.reply(response);
        } else if (path[0] == U("leagues")) {
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

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
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

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
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

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
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

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}
