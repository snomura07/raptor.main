#include "MasterConfig.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

MasterConfig::MasterConfig():
    jsonPath("/usr/local/config/MasterConfig.json"),
    localhost(""),
    raptorIp(""),
    subPort(0),
    pubPort(0),
    configPath("/usr/local/config/"),
    imagePath("/usr/local/image/"),
    cameraPath("/usr/local/image/camera/"),
    logPath("/usr/local/log/"),
    mapFmt()
{}

MasterConfig::~MasterConfig(){}


void MasterConfig::read(){
    std::ifstream jsonFile(jsonPath);

    if (jsonFile.is_open()) {
        jsonFile >> jsonData;
        localhost  = jsonData["localhost"];
        raptorIp   = jsonData["raptorIp"];
        subPort    = jsonData["subPort"];
        pubPort    = jsonData["pubPort"];
        configPath = jsonData["path"]["config"];
        imagePath  = jsonData["path"]["image"];
        cameraPath = jsonData["path"]["camera"];
        logPath    = jsonData["path"]["log"];

        mapFmt["localhost"]  = localhost;
        mapFmt["raptorIp"]   = raptorIp;
        mapFmt["subPort"]    = subPort;
        mapFmt["pubPort"]    = pubPort;
        mapFmt["configPath"] = configPath;
        mapFmt["imagePath"]  = imagePath;
        mapFmt["cameraPath"] = cameraPath;
        mapFmt["logPath"]    = logPath;
    }
    else{
        std::cerr << "file open error" << std::endl;
    }
}

std::string MasterConfig::getStringFromMap(std::string key)
{
    auto it = mapFmt.find(key);
    if (it != mapFmt.end()) {
        if (std::holds_alternative<std::string>(it->second)) {
            return std::get<std::string>(it->second);
        } else {
            throw std::runtime_error("Key does not hold a string value");
        }
    } else {
        throw std::runtime_error("Key not found in map");
    }
}

int MasterConfig::getIntFromMap(std::string key)
{
    auto it = mapFmt.find(key);
    if (it != mapFmt.end()) {
        if (std::holds_alternative<int>(it->second)) {
            return std::get<int>(it->second);
        } else {
            throw std::runtime_error("Key does not hold an int value");
        }
    } else {
        throw std::runtime_error("Key not found in map");
    }
}
