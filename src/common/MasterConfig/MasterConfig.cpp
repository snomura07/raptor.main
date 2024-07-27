#include "MasterConfig.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

MasterConfig::MasterConfig():
    jsonPath("/usr/local/config/MasterConfig.json"),
    subPort(0),
    pubPort(0),
    configPath("/usr/local/config/")
{}

MasterConfig::~MasterConfig(){}


void MasterConfig::read(){
    std::ifstream jsonFile(jsonPath);

    if (jsonFile.is_open()) {
        jsonFile >> jsonData;
        subPort = jsonData["subPort"];
        pubPort = jsonData["pubPort"];
        configPath = jsonData["path"]["config"];
    }
    else{
        std::cerr << "file open error" << std::endl;
    }
}
