#include <thread>
#include <string>
#include "RaptorBase.h"

RaptorBase::RaptorBase():
    modName(""),
    commPort(0){}
RaptorBase::~RaptorBase(){}

bool RaptorBase::runKeepAliveServer()
{
    if(this->commPort == 0){
        return false;
    }

    zmq.registerSession("*", this->commPort, ZmqWrapper::zmqPatternEnum::REPLY, "HELTHCHECK");
    std::thread th([&]() {
        while (true) {
            std::string msg = "";
            auto res = zmq.pollMessage(msg, -1);
            zmq.sendMessage("alive");
        }
    });

    th.join();
    return true;
}
