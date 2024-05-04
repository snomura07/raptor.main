#include <iostream>
#include <fstream>
#include "Counter.h"
#include <ZmqWrapper/ZmqWrapper.h>
#include <CounterMsg/CounterMsg.pb.h>
#include <msleep.hpp>

Counter::Counter():
    count(0)
{
    this->config.read();

    // base用の設定
    this->modName  = this->config.modName;
    this->commPort = this->config.healthCheckcPort;
    this->runKeepAliveServer();
}

Counter::~Counter(){}

bool Counter::run()
{
    bool isRunning = true;
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5556, ZmqWrapper::zmqPatternEnum::PUBLISH, this->config.publishTopic);

    while(isRunning){
        count++;

        raptor::protobuf::CounterMsg counterMsg;
        counterMsg.set_viewname1("counter");
        counterMsg.set_counter(this->count);

        std::string sMsg;
        counterMsg.SerializeToString(&sMsg);
        zmq.sendMessage(sMsg);

        msleep(1000);
    }

    return isRunning;
}
