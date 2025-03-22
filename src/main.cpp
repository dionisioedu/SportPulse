#include <iostream>
#include <thread>
#include <chrono>
#include "ApiClient.h"
#include "Cache.h"

int main() {
    ApiClient client;
    Cache<std::string, std::string> cache;

    while (true) {
        std::string result = client.fetchLiveScores();
        std::cout << result << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}