#include <iostream>
#include <string>
#include <zmq.h>
#include <cstring>
#include <CounterMsg/CounterMsg.pb.h>
#include <ZmqWrapper/ZmqWrapper.h>
#include "../config/AppConfig.h"

void receiveMsg(std::string msg, std::string topic)
{
    raptor::protobuf::CounterMsg counterMsg;
    counterMsg.ParseFromString(msg);

    std::cout << "@" << counterMsg.viewname1() << std::endl;
    std::cout << "Count: " << counterMsg.counter() << std::endl;
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
