#include <iostream>
#include <fstream>
#include "GpioServer.h"
#include <print.hpp>
#include <ZmqWrapper/ZmqWrapper.h>
#include <GpioServerMsg/GpioServerMsg.pb.h>

GpioServer::GpioServer()
{
    config.read();

    // base用の設定
    RaptorBase::modName  = config.modName;
    RaptorBase::commPort = config.healthCheckcPort;
    RaptorBase::runKeepAliveServer();
    RaptorBase::showActivatedSign();
    RaptorBase::initLogger();

    gpio.init();
}

GpioServer::~GpioServer()
{
    RaptorBase::logger.writeInfoLog("finish!");
}

bool GpioServer::run()
{
    bool isRunning = true;
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1",
                        config.master.subPort ,
                        ZmqWrapper::zmqPatternEnum::SUBSCRIBE,
                        config.subscribeTopic,
                        std::bind(&GpioServer::receiveMsg, this, std::placeholders::_1, std::placeholders::_1));
    while(isRunning){
        std::string msg = "";
        auto res = zmq.pollMessage(msg, -1);
    }

    return isRunning;
}

void GpioServer::receiveMsg(std::string msg, std::string topic)
{
    raptor::protobuf::GpioServerMsg protoMsg;
    protoMsg.ParseFromString(msg);
    if(protoMsg.type() == raptor::protobuf::GpioServerMsg::CH_OUTPUT){
        print("CH_OUTPUT port:" , protoMsg.port());
        gpio.chModeOutput(protoMsg.port());
    }
    else if(protoMsg.type() == raptor::protobuf::GpioServerMsg::CH_INPUT){
        print("CH_INPUT port:" , protoMsg.port());
        gpio.chModeInput(protoMsg.port());
    }
    else if(protoMsg.type() == raptor::protobuf::GpioServerMsg::SET_HIGH){
        print("SET_HIGH port:" , protoMsg.port());
        gpio.setHigh(protoMsg.port());
    }
    else if(protoMsg.type() == raptor::protobuf::GpioServerMsg::SET_LOW){
        print("SET_LOW port:" , protoMsg.port());
        gpio.setLow(protoMsg.port());
    }
}
