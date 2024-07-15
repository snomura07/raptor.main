#include <iostream>
#include <thread>
#include <string>
#include "RaptorBase.h"

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
    if(this->commPort == 0){
        return false;
    }

    zmq.registerSession("*", this->commPort, ZmqWrapper::zmqPatternEnum::REPLY, "HELTHCHECK");
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
    std::cout << "[@] " << modName << " start!" << std::endl;
}
