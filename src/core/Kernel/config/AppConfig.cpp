#include "AppConfig.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

AppConfig::AppConfig():
    jsonPath("/opt/raptor/config/Kernel.json"),
    modName(""),
    healthCheckcPort(0)
{}
AppConfig::~AppConfig(){}

void AppConfig::read(){
    master.read();
    jsonPath = master.configPath + "Kernel.json";

    std::ifstream jsonFile(jsonPath);
    if (jsonFile.is_open()) {
        jsonFile >> jsonData;
        modName          = jsonData["modName"];
        healthCheckcPort = jsonData["healthCheckPort"];

        for (const auto& processJson : jsonData["LaunchProcesses"]) {
            Process process;
            process.mod    = processJson["mod"];
            process.launch = processJson["launch"];
            if(process.launch == true){
                LaunchProcesses.push_back(process);
            }
        }
    }
    else{
        std::cerr << "file open error" << std::endl;
    }
}

void AppConfig::dump(){
    std::cout << jsonData.dump() << std::endl;
}
