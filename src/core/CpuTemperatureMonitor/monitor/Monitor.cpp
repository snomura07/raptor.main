#include <iostream>
#include <string>
#include <zmq.h>
#include <cstring>
#include <CpuTemperatureMsg/CpuTemperatureMsg.pb.h>
#include <ZmqWrapper/ZmqWrapper.h>
#include "../config/AppConfig.h"

void receiveMsg(std::string msg, std::string topic)
{
    raptor::protobuf::CpuTemperatureMsg protoMsg;
    protoMsg.ParseFromString(msg);

    std::cout << "@" << protoMsg.viewname1() << std::endl;
    std::cout << "temp: " << protoMsg.cputemperature() << std::endl;
}

int main()
{
    AppConfig config;
    config.read();
    int subPort       = config.master.subPort;
    std::string topic = config.publishTopic;

    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", subPort , ZmqWrapper::zmqPatternEnum::SUBSCRIBE, topic, &receiveMsg);

    while (true) {
        std::string msg = "";
        auto res = zmq.pollMessage(msg, 100);
    }

    return 0;
}
