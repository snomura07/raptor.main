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

        std::string formattedConfig;
        formattedConfig += configPath + "\n{\n";
        for (const auto& [key, value] : configData.items()) {
            formattedConfig += "    \"" + key + "\": ";
            
            if (value.is_string()) {
                formattedConfig += "\"" + value.get<std::string>() + "\"";
            } 
            else if (value.is_number()) {
                formattedConfig += std::to_string(value.get<int>());
            } 
            else if (value.is_boolean()) {
                formattedConfig += value.get<bool>() ? "true" : "false";
            } 
            else if (value.is_array()) {
                formattedConfig += "[\n";
                for (const auto& item : value) {
                    formattedConfig += "        ";
                    if (item.is_object()) {
                        formattedConfig += "{\n";
                        for (const auto& [subKey, subValue] : item.items()) {
                            formattedConfig += "            \"" + subKey + "\": ";
                            if (subValue.is_string()) {
                                formattedConfig += "\"" + subValue.get<std::string>() + "\"";
                            } 
                            else if (subValue.is_number()) {
                                formattedConfig += std::to_string(subValue.get<int>());
                            } 
                            else if (subValue.is_boolean()) {
                                formattedConfig += subValue.get<bool>() ? "true" : "false";
                            } 
                            else {
                                formattedConfig += subValue.dump();
                            }
                            formattedConfig += ",\n";
                        }
                        if (!item.empty()) {
                            formattedConfig.pop_back();  // 最後のカンマを削除
                            formattedConfig.pop_back();  // 最後の改行を削除
                        }
                        formattedConfig += "\n        }";
                    } else {
                        formattedConfig += item.dump();
                    }
                    formattedConfig += ",\n";
                }
                if (!value.empty()) {
                    formattedConfig.pop_back();  // 最後のカンマを削除
                    formattedConfig.pop_back();  // 最後の改行を削除
                }
                formattedConfig += "\n    ]";
            }
            else if (value.is_object()) {
                formattedConfig += "{\n";
                for (const auto& [subKey, subValue] : value.items()) {
                    formattedConfig += "        \"" + subKey + "\": ";
                    if (subValue.is_string()) {
                        formattedConfig += "\"" + subValue.get<std::string>() + "\"";
                    } 
                    else if (subValue.is_number()) {
                        formattedConfig += std::to_string(subValue.get<int>());
                    } 
                    else if (subValue.is_boolean()) {
                        formattedConfig += subValue.get<bool>() ? "true" : "false";
                    } 
                    else {
                        formattedConfig += subValue.dump();
                    }
                    formattedConfig += ",\n";
                }
                if (!value.empty()) {
                    formattedConfig.pop_back();  // 最後のカンマを削除
                    formattedConfig.pop_back();  // 最後の改行を削除
                }
                formattedConfig += "\n    }";
            }
            else {
                formattedConfig += value.dump();
            }
            
            formattedConfig += ",\n";
        }
        
        if (!formattedConfig.empty()) {
            formattedConfig.pop_back();  // 最後のカンマを削除
            formattedConfig.pop_back();  // 最後の改行を削除
        }
        
        return formattedConfig + "\n}";

        configFile.close();
    } else {
        return "{\"error\": \"config not found\"}";
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
