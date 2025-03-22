cmake_minimum_required(VERSION 3.14)
project(SportPulse)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(SportPulse
        src/main.cpp)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(SportPulseTests
        tests/test_main.cpp)
target_link_libraries(SportPulseTests gtest_main)

include(GoogleTest)
gtest_discover_tests(SportPulseTests)