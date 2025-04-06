#include <nlohmann/json.hpp>
#include "services/SearchService.h"
#include "utils/Cache.h"

using json = nlohmann::json;

static Cache<std::string, std::vector<Team>> cache;

std::vector<Team> SearchService::searchTeamsByName(const std::string teamName) {

    if (auto cached = cache.get(teamName); cached.has_value()) {
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

    cache.put(teamName, teams, std::chrono::hours(1));

    return teams;
}

std::vector<Team> SearchService::searchTeamsByShortCode(const std::string shortCode) {

    if (auto cached = cache.get(shortCode); cached.has_value()) {
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

    cache.put(shortCode, teams, std::chrono::hours(1));

    return teams;
}