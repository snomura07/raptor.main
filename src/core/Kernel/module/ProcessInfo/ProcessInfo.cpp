#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <ZmqWrapper/ZmqWrapper.h>
#include <MasterLineMsg/MasterLineMsg.pb.h>
#include <print.hpp>
#include "ProcessInfo.h"

ProcessInfo::ProcessInfo(std::string jsonPath):
    healthCheckPort(0),
    aliveFlag(false),
    preAliveFlag(false)
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

ProcessInfo::~ProcessInfo(){
}

void ProcessInfo::init()
{
    zmq.registerSession("127.0.0.1", healthCheckPort, ZmqWrapper::zmqPatternEnum::REQUEST, "HELTHCHECK");
}

void ProcessInfo::checkAlive()
{
    std::string smsg = "";
    raptor::protobuf::MasterLineMsg masterLineMsg;
    masterLineMsg.set_type(raptor::protobuf::MasterLineMsg::HEALTH_CHECK);
    masterLineMsg.SerializeToString(&smsg);
    zmq.sendMessage(smsg);

    auto res     = zmq.pollMessage(smsg, 100);
    preAliveFlag = aliveFlag;

    if(res < 0){
        aliveFlag = false;
    }
    else{
        aliveFlag = true;
    }
}

bool ProcessInfo::isAlive()
{
    return aliveFlag;
}

bool ProcessInfo::isModified()
{
    return aliveFlag != preAliveFlag;
}

void ProcessInfo::shutdown()
{
    std::string smsg = "";
    raptor::protobuf::MasterLineMsg masterLineMsg;
    masterLineMsg.set_type(raptor::protobuf::MasterLineMsg::SHUTDOWN_REQUEST);
    masterLineMsg.SerializeToString(&smsg);
    zmq.sendMessage(smsg);

    auto res     = zmq.pollMessage(smsg, 100);
    preAliveFlag = aliveFlag;

    if(res < 0){
        aliveFlag = false;
    }
    else{
        aliveFlag = true;
    }
}
