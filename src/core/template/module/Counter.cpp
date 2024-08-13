#include <iostream>
#include <fstream>
#include "Counter.h"
#include <ZmqWrapper/ZmqWrapper.h>
#include <CounterMsg/CounterMsg.pb.h>
#include <msleep.hpp>

Counter::Counter():
    count(0)
{
    config.read();
std::cout << config.master.subPort << " " << config.master.configPath << std::endl;
    // base用の設定
    modName  = config.modName;
    commPort = config.healthCheckcPort;
    runKeepAliveServer();
    showActivatedSign();
    initLogger();
}

Counter::~Counter()
{
    logger.writeInfoLog("finish!");
}

bool Counter::run()
{
    logger.writeInfoLog("start!");

    bool isRunning = true;
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5556, ZmqWrapper::zmqPatternEnum::PUBLISH, config.publishTopic);

    while(isRunning){
        count++;

        raptor::protobuf::CounterMsg counterMsg;
        counterMsg.set_viewname1("counter");
        counterMsg.set_counter(count);

        std::string sMsg;
        counterMsg.SerializeToString(&sMsg);
        zmq.sendMessage(sMsg);

        msleep(1000);
    }

    return isRunning;
}
