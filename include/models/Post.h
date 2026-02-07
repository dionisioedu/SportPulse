#pragma once

#include <string>
#include <vector>

struct Post {
    std::string id;

    std::string title;
    std::string summary;

    std::string imageUrl;
    std::string sourceName;
    std::string sourceUrl;

    long long publishedAtEpochSec = 0; // epoch seconds
    long long updatedAtEpochSec = 0;

    std::vector<std::string> tags;
};
