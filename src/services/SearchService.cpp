#include <nlohmann/json.hpp>
#include "services/SearchService.h"
#include "utils/Cache.h"

using json = nlohmann::json;

static Cache<std::string, std::vector<Team>> teamCache;
static Cache<std::string, std::vector<Player>> playerCache;

std::vector<Team> SearchService::searchTeamsByName(const std::string teamName) {

    if (auto cached = teamCache.get(teamName); cached.has_value()) {
        return cached.value();
    }

    log.log(ILogger::Level::DEBUG, "SearchService requesting ApiClient for searchTeams: " + teamName);

    std::string response = apiClient.searchTeams(teamName);
    log.log(ILogger::Level::DEBUG, "Response: " + response);

    std::vector<Team> teams;
    try {
        auto j = json::parse(response);
        if (j.contains("teams") && j["teams"].is_array()) {
            for (const auto& item : j["teams"]) {
                teams.push_back(Team(item));
            }
        }
    } catch (std::exception& e) {
        std::string error_message("Error parsin JSON: " + std::string(e.what()));
        log.log(ILogger::Level::ERROR, error_message);
    }

    teamCache.put(teamName, teams, std::chrono::hours(1));

    return teams;
}

std::vector<Team> SearchService::searchTeamsByShortCode(const std::string shortCode) {

    if (auto cached = teamCache.get(shortCode); cached.has_value()) {
        return cached.value();
    }

    log.log(ILogger::Level::DEBUG, "SearchService requesting ApiClient for searchTeamsByShortCode: " + shortCode);

    std::string response = apiClient.searchTeamsByShortCode(shortCode);
    log.log(ILogger::Level::DEBUG, "Response: " + response);

    std::vector<Team> teams;
    try {
        auto j = json::parse(response);
        if (j.contains("teams") && j["teams"].is_array()) {
            for (const auto& item : j["teams"]) {
                teams.push_back(Team(item));
            }
        }
    } catch (std::exception& e) {
        std::string error_message("Error parsin JSON: " + std::string(e.what()));
        log.log(ILogger::Level::ERROR, error_message);
    }

    teamCache.put(shortCode, teams, std::chrono::hours(1));

    return teams;
}

std::vector<Player> SearchService::searchPlayers(const std::string playerName) {

    if (auto cached = playerCache.get(playerName); cached.has_value()) {
        return cached.value();
    }

    log.log(ILogger::Level::DEBUG, "SearchService requesting ApiClient for searchPlayers: " + playerName);

    std::string response = apiClient.searchPlayers(playerName);
    log.log(ILogger::Level::DEBUG, "Response: " + response);

    std::vector<Player> players;
    try {
        auto j = json::parse(response);
        if (j.contains("player") && j["player"].is_array()) {
            for (const auto& item : j["player"]) {
                players.push_back(Player(item));
            }
        }
    } catch (std::exception& e) {
        std::string error_message("Error parsin JSON: " + std::string(e.what()));
        log.log(ILogger::Level::ERROR, error_message);
    }

    playerCache.put(playerName, players, std::chrono::hours(1));

    return players;
}

std::vector<Player> SearchService::searchPlayersFromTeam(const std::string teamName) {

    if (auto cached = playerCache.get(teamName); cached.has_value()) {
        return cached.value();
    }

    log.log(ILogger::Level::DEBUG, "SearchService requesting ApiClient for searchPlayersByTeam: " + teamName);

    std::string response = apiClient.searchPlayersFromTeam(teamName);
    log.log(ILogger::Level::DEBUG, "Response: " + response);

    std::vector<Player> players;
    try {
        auto j = json::parse(response);
        if (j.contains("player") && j["player"].is_array()) {
            for (const auto& item : j["player"]) {
                players.push_back(Player(item));
            }
        }
    } catch (std::exception& e) {
        std::string error_message("Error parsin JSON: " + std::string(e.what()));
        log.log(ILogger::Level::ERROR, error_message);
    }

    playerCache.put(teamName, players, std::chrono::hours(1));

    return players;
}