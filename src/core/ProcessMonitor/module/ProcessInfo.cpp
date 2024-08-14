#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <print.hpp>
#include "ProcessInfo.h"

ProcessInfo::ProcessInfo(std::string jsonPath):
    healthCheckPort(0),
    activeFlag(false)
{
    std::ifstream jsonFile(jsonPath);
    if (jsonFile.is_open()) {
        nlohmann::json jsonData;
        jsonFile >> jsonData;
        modName         = jsonData["modName"];
        healthCheckPort = jsonData["healthCheckPort"];
    }
    else{
        std::cerr << "file open error" << std::endl;
    }
}

ProcessInfo::~ProcessInfo(){}

void ProcessInfo::checkAlive()
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", healthCheckPort, ZmqWrapper::zmqPatternEnum::REQUEST, "HELTHCHECK");
    zmq.sendMessage("check");

    std::string rmsg = "";
    auto res = zmq.pollMessage(rmsg, 10);
    if(res < 0){
        activeFlag = false;
    }
    else{
        activeFlag = true;
    }
}

bool ProcessInfo::isActive()
{
    return activeFlag;
}
