#include "Env.h"

bool isDevEnv()
{
    std::ifstream envFile("/opt/raptor/config/env");
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
