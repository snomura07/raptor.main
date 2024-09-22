#include <iostream>
#include <string>
#include <cstring>
#include <print.hpp>
#include <ProcessMonitorMsg/ProcessMonitorMsg.pb.h>
#include <ZmqWrapper/ZmqWrapper.h>
#include "../config/AppConfig.h"

void receiveMsg(std::string msg, std::string topic)
{
    raptor::protobuf::ProcessMonitorMsg processMonitorMsg;
    processMonitorMsg.ParseFromString(msg);
    print(processMonitorMsg.status());
}

int main()
{
    AppConfig config;
    config.read();

    ZmqWrapper zmq;
    zmq.registerSession(
        config.master.localhost, 
        config.master.subPort, 
        ZmqWrapper::zmqPatternEnum::SUBSCRIBE, 
        config.master.processMonitorTopic,
        &receiveMsg
    );


    while (true) {
        std::string msg = "";
        auto res = zmq.pollMessage(msg, -1);
    }

    return 0;
}
