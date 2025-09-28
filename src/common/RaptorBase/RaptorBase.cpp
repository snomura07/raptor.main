#include <iostream>
#include <thread>
#include <string>
#include "RaptorBase.h"
#include <print.hpp>
#include <msleep.hpp>
#include <MasterLineMsg/MasterLineMsg.pb.h>

RaptorBase::RaptorBase():
    modName(""),
    commPort(0),
    shutdownCommandReceived(false)
{}

RaptorBase::~RaptorBase()
{
    if(th.joinable()){
        th.join();
    }
}

void RaptorBase::init(std::string modName_, int commPort_)
{
    modName  = modName_;
    commPort = commPort_;
    runKeepAliveServer();
    showActivatedSign();
    initLogger();
}

void RaptorBase::initLogger()
{
    logger.init(modName);
}

bool RaptorBase::runKeepAliveServer()
{
    if(commPort == 0){
        return false;
    }

    zmq.registerSession("*", commPort, ZmqWrapper::zmqPatternEnum::REPLY, "HELTHCHECK");
    th = std::thread([&]() {
        while (!shutdownCommandReceived) {
            std::string msg = "";
            auto res = zmq.pollMessage(msg, -1);
            raptor::protobuf::MasterLineMsg masterLineMsg;
            masterLineMsg.ParseFromString(msg);

            if(masterLineMsg.type() == raptor::protobuf::MasterLineMsg::HEALTH_CHECK){
                zmq.sendMessage("alive");
            }
            else if(masterLineMsg.type() == raptor::protobuf::MasterLineMsg::SHUTDOWN_REQUEST){
                shutdownCommandReceived = true;
                zmq.sendMessage("shutdown requested");
                logger.writeInfoLog("shutdown request received");
                msleep(100); // 少し待ってから終了
            }
        }
    });

    return true;
}

void RaptorBase::showActivatedSign()
{
    print("[@]", modName, "start!");
}

bool RaptorBase::isRunning()
{
    return !shutdownCommandReceived;
}
