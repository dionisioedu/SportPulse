cmake_minimum_required(VERSION 3.14)
project(SportPulse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(SportPulse
        src/main.cpp
        src/CLIInterface.cpp
        src/apis/TheSportsDbApiClient.cpp
        src/RestServer.cpp
        src/DataProcessor.cpp
        src/services/SportService.cpp
        src/services/LeagueService.cpp
        src/services/CountryService.cpp
        src/services/SearchService.cpp
        src/services/PostService.cpp)

target_link_libraries(SportPulse curl pthread crypto ssl cpprest)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(SportPulseTests
        tests/test_main.cpp
        tests/test_thesportsdbapi.cpp
        tests/test_cache.cpp
        tests/test_sportservice.cpp
        tests/test_leagueservice.cpp
        tests/test_countryservice.cpp
        tests/test_searchservice.cpp
        src/apis/TheSportsDbApiClient.cpp
        src/DataProcessor.cpp
        src/services/SportService.cpp
        src/services/LeagueService.cpp
        src/services/CountryService.cpp
        src/services/SearchService.cpp)

target_link_libraries(SportPulseTests gtest_main curl)

include(GoogleTest)
gtest_discover_tests(SportPulseTests)