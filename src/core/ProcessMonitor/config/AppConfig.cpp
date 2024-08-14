#include "AppConfig.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

AppConfig::AppConfig():
    jsonPath("/usr/local/config/ProcessMonitor.json"),
    modName(""),
    healthCheckcPort(0)
{}
AppConfig::~AppConfig(){}

void AppConfig::read(){
    master.read();
    jsonPath = master.configPath + "ProcessMonitor.json";

    std::ifstream jsonFile(jsonPath);
    if (jsonFile.is_open()) {
        jsonFile >> jsonData;
        modName          = jsonData["modName"];
        healthCheckcPort = jsonData["healthCheckPort"];
    }
    else{
        std::cerr << "file open error" << std::endl;
    }
}

void AppConfig::dump(){
    std::cout << jsonData.dump() << std::endl;
}
