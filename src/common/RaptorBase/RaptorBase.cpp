#include <iostream>
#include <thread>
#include <string>
#include "RaptorBase.h"
#include <print.hpp>

RaptorBase::RaptorBase():
    modName(""),
    commPort(0){}

RaptorBase::~RaptorBase()
{
    if(th.joinable()){
        th.join();
    }
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
        while (true) {
            std::string msg = "";
            auto res = zmq.pollMessage(msg, -1);
            zmq.sendMessage("alive");
        }
    });

    return true;
}

void RaptorBase::showActivatedSign()
{
    print("[@]", modName, "start!");
}
