#include "RestServer.h"
#include <cpprest/json.h>

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
            handleGetLeagues(request);
        } else if (path[0] == U("sports")) {
            handleGetSports(request);
        } else if (path[0] == U("countries")) {
            handleGetCountries(request);
        } else if (path[0] == U("leaguesForCountry")) {
            handleGetLeaguesForCountry(request);
        } else if (path[0] == U("searchTeamsByName")) {
            handleSearchTeamsByName(request);
        } else if (path[0] == U("searchTeamsByShortCode")) {
            handleSearchTeamsByShortCode(request);
        } else if (path[0] == U("searchPlayers")) {
            handleSearchPlayers(request);
        } else if (path[0] == U("searchPlayersFromTeam")) {
            handleSearchPlayersFromTeam(request);
        } else if (path[0] == U("searchEventByName")) {
            handleSearchEventByName(request);
        } else if (path[0] == U("searchEventByNameAndYear")) {
            handleSearchEventsByNameAndYear(request);
        } else if (path[0] == U("searchEventByEventFileName")) {
            handleSearchEventByEventFileName(request);
        } else if (path[0] == U("searchForVenue")) {
            handleSearchForVenue(request);
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

void RestServer::handleGetLeagues(web::http::http_request request) {
    _logger.log(ILogger::Level::INFO, "Received GET request for leagues.");

    auto leagues = _leagueService.getLeagues();
    
    auto jArray = web::json::value::array();
    for (size_t i = 0; i < leagues.size(); ++i) {
        web::json::value jLeague;
        jLeague[U("idLeague")] = web::json::value::string(utility::conversions::to_string_t(leagues[i].idLeague));
        jLeague[U("strLeague")] = web::json::value::string(utility::conversions::to_string_t(leagues[i].strLeague));
        jLeague[U("strSport")] = web::json::value::string(utility::conversions::to_string_t(leagues[i].strSport));
        jLeague[U("strLeagueAlternate")] = web::json::value::string(utility::conversions::to_string_t(leagues[i].strLeagueAlternate));
        jArray[i] = jLeague;
    }

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}

void RestServer::handleGetSports(web::http::http_request request) {
    auto sports = _sportService.getSports();

    auto jArray = web::json::value::array();
    for (size_t i = 0; i < sports.size(); ++i) {
        web::json::value jSport;
        jSport[U("idSport")] = web::json::value::string(utility::conversions::to_string_t(sports[i].idSport));
        jSport[U("strSport")] = web::json::value::string(utility::conversions::to_string_t(sports[i].strSport));

        jArray[i] = jSport;
    }

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}

void RestServer::handleGetCountries(web::http::http_request request) {
    auto countries = _countryService.getCountries();

    auto jArray = web::json::value::array();
    for (size_t i = 0; i < countries.size(); ++i) {
        web::json::value jCountry;
        jCountry[U("name")] = web::json::value::string(utility::conversions::to_string_t(countries[i].name));
        jCountry[U("flag_url")] = web::json::value::string(utility::conversions::to_string_t(countries[i].flag_url));
        jArray[i] = jCountry;
    }

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}

void RestServer::handleGetLeaguesForCountry(web::http::http_request request) {
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
    
    auto jArray = web::json::value::array();
    for (size_t i = 0; i < leagues.size(); ++i) {
        web::json::value jLeague;
        jLeague[U("idLeague")] = web::json::value::string(utility::conversions::to_string_t(leagues[i].idLeague));
        jLeague[U("strLeague")] = web::json::value::string(utility::conversions::to_string_t(leagues[i].strLeague));
        jArray[i] = jLeague;
    }

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}

void RestServer::handleSearchTeamsByName(web::http::http_request request) {
    _logger.log(ILogger::Level::INFO, "Received GET request for searchTeamsByName");

    auto queries = uri::split_query(request.relative_uri().query());
    std::string teamName;
    if (queries.find(U("teamName")) != queries.end()) {
        teamName = utility::conversions::to_utf8string(queries[U("teamName")]);
    }

    if (teamName.empty()) {
        http_response errorResponse(status_codes::BadRequest);
        addCORSHeaders(errorResponse);
        errorResponse.set_body(U("Error: teamName parameter is required."));
        request.reply(errorResponse);
        return;
    }

    auto teams = _searchService.searchTeamsByName(teamName);
    
    auto jArray = web::json::value::array();
    for (size_t i = 0; i < teams.size(); ++i) {
        web::json::value jTeam;
        jTeam[U("idTeam")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idTeam));
        jTeam[U("idESPN")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idESPN));
        jTeam[U("idAPIfootball")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idAPIfootball));
        jTeam[U("intLoved")] = web::json::value::string(utility::conversions::to_string_t(teams[i].intLoved));
        jTeam[U("strTeam")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strTeam));
        jTeam[U("strTeamAlternate")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strTeamAlternate));
        jTeam[U("strTeamShort")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strTeamShort));
        jTeam[U("intFormedYear")] = web::json::value::string(utility::conversions::to_string_t(teams[i].intFormedYear));
        jTeam[U("strSport")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strSport));
        jTeam[U("strLeague")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague));
        jTeam[U("idLeague")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague));
        jTeam[U("strLeague2")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague2));
        jTeam[U("idLeague2")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague2));
        jTeam[U("strLeague3")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague3));
        jTeam[U("idLeague3")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague3));
        jTeam[U("strLeague4")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague4));
        jTeam[U("idLeague4")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague4));
        jTeam[U("strLeague5")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague5));
        jTeam[U("idLeague5")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague5));
        jTeam[U("strLeague6")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague6));
        jTeam[U("idLeague6")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague6));
        jTeam[U("strLeague7")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague7));
        jTeam[U("idLeague7")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague7));
        jTeam[U("strDivision")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strDivision));
        jTeam[U("idVenue")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idVenue));
        jTeam[U("strStadium")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strStadium));
        jTeam[U("strKeywords")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strKeywords));
        jTeam[U("strRSS")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strRSS));
        jTeam[U("strLocation")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLocation));
        jTeam[U("intStadiumCapacity")] = web::json::value::string(utility::conversions::to_string_t(teams[i].intStadiumCapacity));
        jTeam[U("strWebsite")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strWebsite));
        jTeam[U("strFacebook")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strFacebook));
        jTeam[U("strTwitter")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strTwitter));
        jTeam[U("strInstagram")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strInstagram));
        jTeam[U("strDescriptionEN")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strDescriptionEN));
        jTeam[U("strColour1")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strColour1));
        jTeam[U("strColour2")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strColour2));
        jTeam[U("strColour3")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strColour3));
        jTeam[U("strGender")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strGender));
        jTeam[U("strCountry")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strCountry));
        jTeam[U("strBadge")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strBadge));
        jTeam[U("strLogo")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLogo));
        jTeam[U("strFanart1")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strFanart1));
        jTeam[U("strFanart2")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strFanart2));
        jTeam[U("strFanart3")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strFanart3));
        jTeam[U("strFanart4")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strFanart4));
        jTeam[U("strBanner")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strBanner));
        jTeam[U("strEquipment")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strEquipment));
        jTeam[U("strYoutube")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strYoutube));
        jTeam[U("strLocked")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLocked));
        jArray[i] = jTeam;
    }

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}

void RestServer::handleSearchTeamsByShortCode(web::http::http_request request) {
    _logger.log(ILogger::Level::INFO, "Received GET request for searchTeamsByName");

    auto queries = uri::split_query(request.relative_uri().query());
    std::string shortCode;
    if (queries.find(U("shortCode")) != queries.end()) {
        shortCode = utility::conversions::to_utf8string(queries[U("shortCode")]);
    }

    if (shortCode.empty()) {
        http_response errorResponse(status_codes::BadRequest);
        addCORSHeaders(errorResponse);
        errorResponse.set_body(U("Error: shortCode parameter is required."));
        request.reply(errorResponse);
        return;
    }

    auto teams = _searchService.searchTeamsByShortCode(shortCode);
    
    auto jArray = web::json::value::array();
    for (size_t i = 0; i < teams.size(); ++i) {
        web::json::value jTeam;
        jTeam[U("idTeam")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idTeam));
        jTeam[U("idESPN")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idESPN));
        jTeam[U("idAPIfootball")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idAPIfootball));
        jTeam[U("intLoved")] = web::json::value::string(utility::conversions::to_string_t(teams[i].intLoved));
        jTeam[U("strTeam")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strTeam));
        jTeam[U("strTeamAlternate")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strTeamAlternate));
        jTeam[U("strTeamShort")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strTeamShort));
        jTeam[U("intFormedYear")] = web::json::value::string(utility::conversions::to_string_t(teams[i].intFormedYear));
        jTeam[U("strSport")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strSport));
        jTeam[U("strLeague")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague));
        jTeam[U("idLeague")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague));
        jTeam[U("strLeague2")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague2));
        jTeam[U("idLeague2")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague2));
        jTeam[U("strLeague3")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague3));
        jTeam[U("idLeague3")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague3));
        jTeam[U("strLeague4")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague4));
        jTeam[U("idLeague4")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague4));
        jTeam[U("strLeague5")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague5));
        jTeam[U("idLeague5")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague5));
        jTeam[U("strLeague6")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague6));
        jTeam[U("idLeague6")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague6));
        jTeam[U("strLeague7")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLeague7));
        jTeam[U("idLeague7")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idLeague7));
        jTeam[U("strDivision")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strDivision));
        jTeam[U("idVenue")] = web::json::value::string(utility::conversions::to_string_t(teams[i].idVenue));
        jTeam[U("strStadium")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strStadium));
        jTeam[U("strKeywords")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strKeywords));
        jTeam[U("strRSS")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strRSS));
        jTeam[U("strLocation")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLocation));
        jTeam[U("intStadiumCapacity")] = web::json::value::string(utility::conversions::to_string_t(teams[i].intStadiumCapacity));
        jTeam[U("strWebsite")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strWebsite));
        jTeam[U("strFacebook")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strFacebook));
        jTeam[U("strTwitter")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strTwitter));
        jTeam[U("strInstagram")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strInstagram));
        jTeam[U("strDescriptionEN")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strDescriptionEN));
        jTeam[U("strColour1")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strColour1));
        jTeam[U("strColour2")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strColour2));
        jTeam[U("strColour3")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strColour3));
        jTeam[U("strGender")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strGender));
        jTeam[U("strCountry")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strCountry));
        jTeam[U("strBadge")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strBadge));
        jTeam[U("strLogo")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLogo));
        jTeam[U("strFanart1")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strFanart1));
        jTeam[U("strFanart2")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strFanart2));
        jTeam[U("strFanart3")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strFanart3));
        jTeam[U("strFanart4")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strFanart4));
        jTeam[U("strBanner")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strBanner));
        jTeam[U("strEquipment")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strEquipment));
        jTeam[U("strYoutube")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strYoutube));
        jTeam[U("strLocked")] = web::json::value::string(utility::conversions::to_string_t(teams[i].strLocked));
        jArray[i] = jTeam;
    }

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}

void RestServer::handleSearchPlayers(web::http::http_request request) {
    _logger.log(ILogger::Level::INFO, "Received GET request for searchPlayers");

    auto queries = uri::split_query(request.relative_uri().query());
    std::string playerName;
    if (queries.find(U("playerName")) != queries.end()) {
        playerName = utility::conversions::to_utf8string(queries[U("playerName")]);
    }

    if (playerName.empty()) {
        http_response errorResponse(status_codes::BadRequest);
        addCORSHeaders(errorResponse);
        errorResponse.set_body(U("Error: playerName parameter is required."));
        request.reply(errorResponse);
        return;
    }

    auto players = _searchService.searchPlayers(playerName);

    web::json::value jArray = web::json::value::array();
    for (size_t i = 0; i < players.size(); ++i) {
        web::json::value jPlayer;
        jPlayer[U("idPlayer")] = web::json::value::string(utility::conversions::to_string_t(players[i].idPlayer));
        jPlayer[U("idTeam")] = web::json::value::string(utility::conversions::to_string_t(players[i].idTeam));
        jPlayer[U("strPlayer")] = web::json::value::string(utility::conversions::to_string_t(players[i].strPlayer));
        jPlayer[U("strTeam")] = web::json::value::string(utility::conversions::to_string_t(players[i].strTeam));
        jPlayer[U("strSport")] = web::json::value::string(utility::conversions::to_string_t(players[i].strSport));
        jPlayer[U("strThumb")] = web::json::value::string(utility::conversions::to_string_t(players[i].strThumb));
        jPlayer[U("strCutout")] = web::json::value::string(utility::conversions::to_string_t(players[i].strCutout));
        jPlayer[U("strNationality")] = web::json::value::string(utility::conversions::to_string_t(players[i].strNationality));
        jPlayer[U("dateBorn")] = web::json::value::string(utility::conversions::to_string_t(players[i].dateBorn));
        jPlayer[U("strStatus")] = web::json::value::string(utility::conversions::to_string_t(players[i].strStatus));
        jPlayer[U("strGender")] = web::json::value::string(utility::conversions::to_string_t(players[i].strGender));
        jPlayer[U("strPosition")] = web::json::value::string(utility::conversions::to_string_t(players[i].strPosition));
        jPlayer[U("relevance")] = web::json::value::string(utility::conversions::to_string_t(players[i].relevance));
        jArray[i] = jPlayer;
    }

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}

void RestServer::handleSearchPlayersFromTeam(web::http::http_request request) {
    _logger.log(ILogger::Level::INFO, "Received GET request for searchPlayersFromTeam");

    auto queries = uri::split_query(request.relative_uri().query());
    std::string teamName;
    if (queries.find(U("teamName")) != queries.end()) {
        teamName = utility::conversions::to_utf8string(queries[U("teamName")]);
    }

    if (teamName.empty()) {
        http_response errorResponse(status_codes::BadRequest);
        addCORSHeaders(errorResponse);
        errorResponse.set_body(U("Error: teamName parameter is required."));
        request.reply(errorResponse);
        return;
    }

    auto players = _searchService.searchPlayersFromTeam(teamName);

    web::json::value jArray = web::json::value::array();
    for (size_t i = 0; i < players.size(); ++i) {
        web::json::value jPlayer;
        jPlayer[U("idPlayer")] = web::json::value::string(utility::conversions::to_string_t(players[i].idPlayer));
        jPlayer[U("idTeam")] = web::json::value::string(utility::conversions::to_string_t(players[i].idTeam));
        jPlayer[U("strPlayer")] = web::json::value::string(utility::conversions::to_string_t(players[i].strPlayer));
        jPlayer[U("strTeam")] = web::json::value::string(utility::conversions::to_string_t(players[i].strTeam));
        jPlayer[U("strSport")] = web::json::value::string(utility::conversions::to_string_t(players[i].strSport));
        jPlayer[U("strThumb")] = web::json::value::string(utility::conversions::to_string_t(players[i].strThumb));
        jPlayer[U("strCutout")] = web::json::value::string(utility::conversions::to_string_t(players[i].strCutout));
        jPlayer[U("strNationality")] = web::json::value::string(utility::conversions::to_string_t(players[i].strNationality));
        jPlayer[U("dateBorn")] = web::json::value::string(utility::conversions::to_string_t(players[i].dateBorn));
        jPlayer[U("strStatus")] = web::json::value::string(utility::conversions::to_string_t(players[i].strStatus));
        jPlayer[U("strGender")] = web::json::value::string(utility::conversions::to_string_t(players[i].strGender));
        jPlayer[U("strPosition")] = web::json::value::string(utility::conversions::to_string_t(players[i].strPosition));
        jPlayer[U("relevance")] = web::json::value::string(utility::conversions::to_string_t(players[i].relevance));
        jArray[i] = jPlayer;
    }

    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}

void RestServer::handleSearchEventByName(web::http::http_request request) {
    _logger.log(ILogger::Level::INFO, "Received GET request for searchEventByName");

    auto queries = uri::split_query(request.relative_uri().query());
    std::string eventName;
    if (queries.find(U("eventName")) != queries.end()) {
        eventName = utility::conversions::to_utf8string(queries[U("eventName")]);
    }
    
    if (eventName.empty()) {
        http_response errorResponse(status_codes::BadRequest);
        addCORSHeaders(errorResponse);
        errorResponse.set_body(U("Error: eventName parameter is required."));
        request.reply(errorResponse);
        return;
    }
    
    auto events = _searchService.searchEventByName(eventName);
    
    web::json::value jArray = web::json::value::array();
    for (size_t i = 0; i < events.size(); ++i) {
        web::json::value jEvent;
        jEvent[U("idEvent")] = web::json::value::string(utility::conversions::to_string_t(events[i].idEvent));
        jEvent[U("idAPIfootball")] = web::json::value::string(utility::conversions::to_string_t(events[i].idAPIfootball));
        jEvent[U("strEvent")] = web::json::value::string(utility::conversions::to_string_t(events[i].strEvent));
        jEvent[U("strEventAlternate")] = web::json::value::string(utility::conversions::to_string_t(events[i].strEventAlternate));
        jEvent[U("strFilename")] = web::json::value::string(utility::conversions::to_string_t(events[i].strFilename));
        jEvent[U("strSport")] = web::json::value::string(utility::conversions::to_string_t(events[i].strSport));
        jEvent[U("idLeague")] = web::json::value::string(utility::conversions::to_string_t(events[i].idLeague));
        jEvent[U("strLeague")] = web::json::value::string(utility::conversions::to_string_t(events[i].strLeague));
        jEvent[U("strLeagueBadge")] = web::json::value::string(utility::conversions::to_string_t(events[i].strLeagueBadge));
        jEvent[U("strSeason")] = web::json::value::string(utility::conversions::to_string_t(events[i].strSeason));
        jEvent[U("strDescriptionEN")] = web::json::value::string(utility::conversions::to_string_t(events[i].strDescriptionEN));
        jEvent[U("strHomeTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].strHomeTeam));
        jEvent[U("strAwayTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].strAwayTeam));
        jEvent[U("intHomeScore")] = web::json::value::string(utility::conversions::to_string_t(events[i].intHomeScore));
        jEvent[U("intAwayScore")] = web::json::value::string(utility::conversions::to_string_t(events[i].intAwayScore));
        jEvent[U("intRound")] = web::json::value::string(utility::conversions::to_string_t(events[i].intRound));
        jEvent[U("intSpectators")] = web::json::value::string(utility::conversions::to_string_t(events[i].intSpectators));
        jEvent[U("strOfficial")] = web::json::value::string(utility::conversions::to_string_t(events[i].strOfficial));
        jEvent[U("strTimestamp")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTimestamp));
        jEvent[U("dateEvent")] = web::json::value::string(utility::conversions::to_string_t(events[i].dateEvent));
        jEvent[U("dateEventLocal")] = web::json::value::string(utility::conversions::to_string_t(events[i].dateEventLocal));
        jEvent[U("strTime")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTime));
        jEvent[U("strTimeLocal")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTimeLocal));
        jEvent[U("strGroup")] = web::json::value::string(utility::conversions::to_string_t(events[i].strGroup));
        jEvent[U("idHomeTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].idHomeTeam));
        jEvent[U("strHomeTeamBadge")] = web::json::value::string(utility::conversions::to_string_t(events[i].strHomeTeamBadge));
        jEvent[U("idAwayTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].idAwayTeam));
        jEvent[U("strAwayTeamBadge")] = web::json::value::string(utility::conversions::to_string_t(events[i].strAwayTeamBadge));
        jEvent[U("intScore")] = web::json::value::string(utility::conversions::to_string_t(events[i].intScore));
        jEvent[U("intScoreVotes")] = web::json::value::string(utility::conversions::to_string_t(events[i].intScoreVotes));
        jEvent[U("strResult")] = web::json::value::string(utility::conversions::to_string_t(events[i].strResult));
        jEvent[U("idVenue")] = web::json::value::string(utility::conversions::to_string_t(events[i].idVenue));
        jEvent[U("strVenue")] = web::json::value::string(utility::conversions::to_string_t(events[i].strVenue));
        jEvent[U("strCountry")] = web::json::value::string(utility::conversions::to_string_t(events[i].strCountry));
        jEvent[U("strCity")] = web::json::value::string(utility::conversions::to_string_t(events[i].strCity));
        jEvent[U("strPoster")] = web::json::value::string(utility::conversions::to_string_t(events[i].strPoster));
        jEvent[U("strSquare")] = web::json::value::string(utility::conversions::to_string_t(events[i].strSquare));
        jEvent[U("strFanart")] = web::json::value::string(utility::conversions::to_string_t(events[i].strFanart));
        jEvent[U("strThumb")] = web::json::value::string(utility::conversions::to_string_t(events[i].strThumb));
        jEvent[U("strBanner")] = web::json::value::string(utility::conversions::to_string_t(events[i].strBanner));
        jEvent[U("strMap")] = web::json::value::string(utility::conversions::to_string_t(events[i].strMap));
        jEvent[U("strTweet1")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTweet1));
        jEvent[U("strTweet2")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTweet2));
        jEvent[U("strTweet3")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTweet3));
        jEvent[U("strVideo")] = web::json::value::string(utility::conversions::to_string_t(events[i].strVideo));
        jEvent[U("strStatus")] = web::json::value::string(utility::conversions::to_string_t(events[i].strStatus));
        jEvent[U("strPostponed")] = web::json::value::string(utility::conversions::to_string_t(events[i].strPostponed));
        jEvent[U("strLocked")] = web::json::value::string(utility::conversions::to_string_t(events[i].strLocked));

        jArray[i] = jEvent;
    }
    
    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}

void RestServer::handleSearchEventsByNameAndYear(web::http::http_request request) {
    _logger.log(ILogger::Level::INFO, "Received GET request for searchEventsByNameAndYear");

    auto queries = uri::split_query(request.relative_uri().query());
    std::string eventName;
    std::string startYear;
    std::string endYear;
    if (queries.find(U("eventName")) != queries.end()) {
        eventName = utility::conversions::to_utf8string(queries[U("eventName")]);
    }

    if (queries.find(U("startYear")) != queries.end()) {
        startYear = utility::conversions::to_utf8string(queries[U("startYear")]);
    }

    if (queries.find(U("endYear")) != queries.end()) {
        endYear = utility::conversions::to_utf8string(queries[U("endYear")]);
    }
    
    if (eventName.empty()) {
        http_response errorResponse(status_codes::BadRequest);
        addCORSHeaders(errorResponse);
        errorResponse.set_body(U("Error: eventName parameter is required."));
        request.reply(errorResponse);
        return;
    }

    if (startYear.empty()) {
        http_response errorResponse(status_codes::BadRequest);
        addCORSHeaders(errorResponse);
        errorResponse.set_body(U("Error: startYear parameter is required."));
        request.reply(errorResponse);
        return;
    }

    if (endYear.empty()) {
        http_response errorResponse(status_codes::BadRequest);
        addCORSHeaders(errorResponse);
        errorResponse.set_body(U("Error: endYear parameter is required."));
        request.reply(errorResponse);
        return;
    }
    
    auto events = _searchService.searchEventsByNameAndYear(eventName, startYear, endYear);
    
    web::json::value jArray = web::json::value::array();
    for (size_t i = 0; i < events.size(); ++i) {
        web::json::value jEvent;
        jEvent[U("idEvent")] = web::json::value::string(utility::conversions::to_string_t(events[i].idEvent));
        jEvent[U("idAPIfootball")] = web::json::value::string(utility::conversions::to_string_t(events[i].idAPIfootball));
        jEvent[U("strEvent")] = web::json::value::string(utility::conversions::to_string_t(events[i].strEvent));
        jEvent[U("strEventAlternate")] = web::json::value::string(utility::conversions::to_string_t(events[i].strEventAlternate));
        jEvent[U("strFilename")] = web::json::value::string(utility::conversions::to_string_t(events[i].strFilename));
        jEvent[U("strSport")] = web::json::value::string(utility::conversions::to_string_t(events[i].strSport));
        jEvent[U("idLeague")] = web::json::value::string(utility::conversions::to_string_t(events[i].idLeague));
        jEvent[U("strLeague")] = web::json::value::string(utility::conversions::to_string_t(events[i].strLeague));
        jEvent[U("strLeagueBadge")] = web::json::value::string(utility::conversions::to_string_t(events[i].strLeagueBadge));
        jEvent[U("strSeason")] = web::json::value::string(utility::conversions::to_string_t(events[i].strSeason));
        jEvent[U("strDescriptionEN")] = web::json::value::string(utility::conversions::to_string_t(events[i].strDescriptionEN));
        jEvent[U("strHomeTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].strHomeTeam));
        jEvent[U("strAwayTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].strAwayTeam));
        jEvent[U("intHomeScore")] = web::json::value::string(utility::conversions::to_string_t(events[i].intHomeScore));
        jEvent[U("intAwayScore")] = web::json::value::string(utility::conversions::to_string_t(events[i].intAwayScore));
        jEvent[U("intRound")] = web::json::value::string(utility::conversions::to_string_t(events[i].intRound));
        jEvent[U("intSpectators")] = web::json::value::string(utility::conversions::to_string_t(events[i].intSpectators));
        jEvent[U("strOfficial")] = web::json::value::string(utility::conversions::to_string_t(events[i].strOfficial));
        jEvent[U("strTimestamp")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTimestamp));
        jEvent[U("dateEvent")] = web::json::value::string(utility::conversions::to_string_t(events[i].dateEvent));
        jEvent[U("dateEventLocal")] = web::json::value::string(utility::conversions::to_string_t(events[i].dateEventLocal));
        jEvent[U("strTime")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTime));
        jEvent[U("strTimeLocal")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTimeLocal));
        jEvent[U("strGroup")] = web::json::value::string(utility::conversions::to_string_t(events[i].strGroup));
        jEvent[U("idHomeTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].idHomeTeam));
        jEvent[U("strHomeTeamBadge")] = web::json::value::string(utility::conversions::to_string_t(events[i].strHomeTeamBadge));
        jEvent[U("idAwayTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].idAwayTeam));
        jEvent[U("strAwayTeamBadge")] = web::json::value::string(utility::conversions::to_string_t(events[i].strAwayTeamBadge));
        jEvent[U("intScore")] = web::json::value::string(utility::conversions::to_string_t(events[i].intScore));
        jEvent[U("intScoreVotes")] = web::json::value::string(utility::conversions::to_string_t(events[i].intScoreVotes));
        jEvent[U("strResult")] = web::json::value::string(utility::conversions::to_string_t(events[i].strResult));
        jEvent[U("idVenue")] = web::json::value::string(utility::conversions::to_string_t(events[i].idVenue));
        jEvent[U("strVenue")] = web::json::value::string(utility::conversions::to_string_t(events[i].strVenue));
        jEvent[U("strCountry")] = web::json::value::string(utility::conversions::to_string_t(events[i].strCountry));
        jEvent[U("strCity")] = web::json::value::string(utility::conversions::to_string_t(events[i].strCity));
        jEvent[U("strPoster")] = web::json::value::string(utility::conversions::to_string_t(events[i].strPoster));
        jEvent[U("strSquare")] = web::json::value::string(utility::conversions::to_string_t(events[i].strSquare));
        jEvent[U("strFanart")] = web::json::value::string(utility::conversions::to_string_t(events[i].strFanart));
        jEvent[U("strThumb")] = web::json::value::string(utility::conversions::to_string_t(events[i].strThumb));
        jEvent[U("strBanner")] = web::json::value::string(utility::conversions::to_string_t(events[i].strBanner));
        jEvent[U("strMap")] = web::json::value::string(utility::conversions::to_string_t(events[i].strMap));
        jEvent[U("strTweet1")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTweet1));
        jEvent[U("strTweet2")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTweet2));
        jEvent[U("strTweet3")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTweet3));
        jEvent[U("strVideo")] = web::json::value::string(utility::conversions::to_string_t(events[i].strVideo));
        jEvent[U("strStatus")] = web::json::value::string(utility::conversions::to_string_t(events[i].strStatus));
        jEvent[U("strPostponed")] = web::json::value::string(utility::conversions::to_string_t(events[i].strPostponed));
        jEvent[U("strLocked")] = web::json::value::string(utility::conversions::to_string_t(events[i].strLocked));

        jArray[i] = jEvent;
    }
    
    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}

void RestServer::handleSearchEventByEventFileName(web::http::http_request request) {
    _logger.log(ILogger::Level::INFO, "Received GET request for searchEventByEventFileName");

    auto queries = uri::split_query(request.relative_uri().query());
    std::string eventFileName;
    if (queries.find(U("eventFileName")) != queries.end()) {
        eventFileName = utility::conversions::to_utf8string(queries[U("eventFileName")]);
    }
    
    if (eventFileName.empty()) {
        http_response errorResponse(status_codes::BadRequest);
        addCORSHeaders(errorResponse);
        errorResponse.set_body(U("Error: eventFileName parameter is required."));
        request.reply(errorResponse);
        return;
    }

    auto events = _searchService.searchEventByEventFileName(eventFileName);
    
    web::json::value jArray = web::json::value::array();
    for (size_t i = 0; i < events.size(); ++i) {
        web::json::value jEvent;
        jEvent[U("idEvent")] = web::json::value::string(utility::conversions::to_string_t(events[i].idEvent));
        jEvent[U("idAPIfootball")] = web::json::value::string(utility::conversions::to_string_t(events[i].idAPIfootball));
        jEvent[U("strEvent")] = web::json::value::string(utility::conversions::to_string_t(events[i].strEvent));
        jEvent[U("strEventAlternate")] = web::json::value::string(utility::conversions::to_string_t(events[i].strEventAlternate));
        jEvent[U("strFilename")] = web::json::value::string(utility::conversions::to_string_t(events[i].strFilename));
        jEvent[U("strSport")] = web::json::value::string(utility::conversions::to_string_t(events[i].strSport));
        jEvent[U("idLeague")] = web::json::value::string(utility::conversions::to_string_t(events[i].idLeague));
        jEvent[U("strLeague")] = web::json::value::string(utility::conversions::to_string_t(events[i].strLeague));
        jEvent[U("strLeagueBadge")] = web::json::value::string(utility::conversions::to_string_t(events[i].strLeagueBadge));
        jEvent[U("strSeason")] = web::json::value::string(utility::conversions::to_string_t(events[i].strSeason));
        jEvent[U("strDescriptionEN")] = web::json::value::string(utility::conversions::to_string_t(events[i].strDescriptionEN));
        jEvent[U("strHomeTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].strHomeTeam));
        jEvent[U("strAwayTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].strAwayTeam));
        jEvent[U("intHomeScore")] = web::json::value::string(utility::conversions::to_string_t(events[i].intHomeScore));
        jEvent[U("intAwayScore")] = web::json::value::string(utility::conversions::to_string_t(events[i].intAwayScore));
        jEvent[U("intRound")] = web::json::value::string(utility::conversions::to_string_t(events[i].intRound));
        jEvent[U("intSpectators")] = web::json::value::string(utility::conversions::to_string_t(events[i].intSpectators));
        jEvent[U("strOfficial")] = web::json::value::string(utility::conversions::to_string_t(events[i].strOfficial));
        jEvent[U("strTimestamp")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTimestamp));
        jEvent[U("dateEvent")] = web::json::value::string(utility::conversions::to_string_t(events[i].dateEvent));
        jEvent[U("dateEventLocal")] = web::json::value::string(utility::conversions::to_string_t(events[i].dateEventLocal));
        jEvent[U("strTime")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTime));
        jEvent[U("strTimeLocal")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTimeLocal));
        jEvent[U("strGroup")] = web::json::value::string(utility::conversions::to_string_t(events[i].strGroup));
        jEvent[U("idHomeTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].idHomeTeam));
        jEvent[U("strHomeTeamBadge")] = web::json::value::string(utility::conversions::to_string_t(events[i].strHomeTeamBadge));
        jEvent[U("idAwayTeam")] = web::json::value::string(utility::conversions::to_string_t(events[i].idAwayTeam));
        jEvent[U("strAwayTeamBadge")] = web::json::value::string(utility::conversions::to_string_t(events[i].strAwayTeamBadge));
        jEvent[U("intScore")] = web::json::value::string(utility::conversions::to_string_t(events[i].intScore));
        jEvent[U("intScoreVotes")] = web::json::value::string(utility::conversions::to_string_t(events[i].intScoreVotes));
        jEvent[U("strResult")] = web::json::value::string(utility::conversions::to_string_t(events[i].strResult));
        jEvent[U("idVenue")] = web::json::value::string(utility::conversions::to_string_t(events[i].idVenue));
        jEvent[U("strVenue")] = web::json::value::string(utility::conversions::to_string_t(events[i].strVenue));
        jEvent[U("strCountry")] = web::json::value::string(utility::conversions::to_string_t(events[i].strCountry));
        jEvent[U("strCity")] = web::json::value::string(utility::conversions::to_string_t(events[i].strCity));
        jEvent[U("strPoster")] = web::json::value::string(utility::conversions::to_string_t(events[i].strPoster));
        jEvent[U("strSquare")] = web::json::value::string(utility::conversions::to_string_t(events[i].strSquare));
        jEvent[U("strFanart")] = web::json::value::string(utility::conversions::to_string_t(events[i].strFanart));
        jEvent[U("strThumb")] = web::json::value::string(utility::conversions::to_string_t(events[i].strThumb));
        jEvent[U("strBanner")] = web::json::value::string(utility::conversions::to_string_t(events[i].strBanner));
        jEvent[U("strMap")] = web::json::value::string(utility::conversions::to_string_t(events[i].strMap));
        jEvent[U("strTweet1")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTweet1));
        jEvent[U("strTweet2")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTweet2));
        jEvent[U("strTweet3")] = web::json::value::string(utility::conversions::to_string_t(events[i].strTweet3));
        jEvent[U("strVideo")] = web::json::value::string(utility::conversions::to_string_t(events[i].strVideo));
        jEvent[U("strStatus")] = web::json::value::string(utility::conversions::to_string_t(events[i].strStatus));
        jEvent[U("strPostponed")] = web::json::value::string(utility::conversions::to_string_t(events[i].strPostponed));
        jEvent[U("strLocked")] = web::json::value::string(utility::conversions::to_string_t(events[i].strLocked));

        jArray[i] = jEvent;
    }
    
    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}

void RestServer::handleSearchForVenue(web::http::http_request request) {
    _logger.log(ILogger::Level::INFO, "Received GET request for searchForVenue");

    auto queries = uri::split_query(request.relative_uri().query());
    std::string venueName;
    if (queries.find(U("venueName")) != queries.end()) {
        venueName = utility::conversions::to_utf8string(queries[U("venueName")]);
    }

    if (venueName.empty()) {
        http_response errorResponse(status_codes::BadRequest);
        addCORSHeaders(errorResponse);
        errorResponse.set_body(U("Error: venueName parameter is required."));
        request.reply(errorResponse);
        return;
    }

    auto venues = _searchService.searchForVenue(venueName);

    web::json::value jArray = web::json::value::array();
    for (size_t i = 0; i < venues.size(); ++i) {
        web::json::value jVenue;
        jVenue[U("idVenue")] = web::json::value::string(utility::conversions::to_string_t(venues[i].idVenue));
        jVenue[U("idDupe")] = web::json::value::string(utility::conversions::to_string_t(venues[i].idDupe));
        jVenue[U("strVenue")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strVenue));
        jVenue[U("strVenueAlternate")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strVenueAlternate));
        jVenue[U("strVenueSponsor")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strVenueSponsor));
        jVenue[U("strSport")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strSport));
        jVenue[U("strDescriptionEN")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strDescriptionEN));
        jVenue[U("strArchitect")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strArchitect));
        jVenue[U("intCapacity")] = web::json::value::string(utility::conversions::to_string_t(venues[i].intCapacity));
        jVenue[U("strCost")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strCost));
        jVenue[U("strCountry")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strCountry));
        jVenue[U("strLocation")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strLocation));
        jVenue[U("strTimezone")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strTimezone));
        jVenue[U("intFormedYear")] = web::json::value::string(utility::conversions::to_string_t(venues[i].intFormedYear));
        jVenue[U("strFanart1")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strFanart1));
        jVenue[U("strFanart2")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strFanart2));
        jVenue[U("strFanart3")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strFanart3));
        jVenue[U("strFanart4")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strFanart4));
        jVenue[U("strThumb")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strThumb));
        jVenue[U("strLogo")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strLogo));
        jVenue[U("strMap")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strMap));
        jVenue[U("strWebsite")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strWebsite));
        jVenue[U("strFacebook")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strFacebook));
        jVenue[U("strInstagram")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strInstagram));
        jVenue[U("strTwitter")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strTwitter));
        jVenue[U("strYoutube")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strYoutube));
        jVenue[U("strLocked")] = web::json::value::string(utility::conversions::to_string_t(venues[i].strLocked));

        jArray[i] = jVenue;
    }
    
    http_response response(status_codes::OK);
    addCORSHeaders(response);
    response.headers().add(U("Content-Type"), U("application/json"));
    response.set_body(jArray);
    request.reply(response);
}
