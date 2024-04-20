#ifndef INCLUDE_ENV
#define INCLUDE_ENV

#include <fstream>
#include <string>

bool isDevEnv()
{
    std::ifstream envFile("/usr/local/config/env");
    std::string line;

    if (!envFile.is_open()) {
        return false;
    }

    while (std::getline(envFile, line)) {
        if (line.find("ENV=develop") != std::string::npos) {
            return true;
        }
    }

    return false;
}

#endif
