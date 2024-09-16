#include <fstream>
#include <filesystem>
#include "ConfigController.h"
#include <nlohmann/json.hpp>

ConfigController::ConfigController() {
    masterConfig.read();
}
ConfigController::~ConfigController() {}

std::string ConfigController::getConfig(const std::string& configName) 
{
    std::string configPath = masterConfig.configPath + configName + ".json";
    std::ifstream configFile(configPath);

    if (configFile.is_open()) {
        nlohmann::json configData;
        configFile >> configData;
        return configData.dump(4);
    }
}

std::string ConfigController::getList()
{
    std::string configPath = masterConfig.configPath;
    std::vector<std::string> configFiles;
    for (const auto& entry : std::filesystem::directory_iterator(configPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            configFiles.push_back(entry.path().filename().string());
        }
    }

    nlohmann::json result;
    result["configs"] = configFiles;
    return result.dump(2);
}
