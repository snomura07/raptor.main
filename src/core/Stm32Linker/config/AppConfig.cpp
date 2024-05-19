#include "AppConfig.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

AppConfig::AppConfig():
    jsonPath("/usr/local/config/Stm32Linker.json"),
    modName(""),
    healthCheckcPort(0),
    publishTopic("")
{}
AppConfig::~AppConfig(){}

void AppConfig::read(){
    std::ifstream jsonFile(this->jsonPath);

    if (jsonFile.is_open()) {
        jsonFile >> this->jsonData;
        this->modName          = this->jsonData["modName"];
        this->healthCheckcPort = this->jsonData["healthCheckPort"];
        this->publishTopic     = this->jsonData["publishTopic"];
    }
    else{
        std::cerr << "file open error" << std::endl;
    }
}

void AppConfig::dump(){
    std::cout << this->jsonData.dump() << std::endl;
}