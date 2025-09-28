#include <print.hpp>
#include <str.hpp>
#include <msleep.hpp>
#include "ShutdownGate.h"

ShutdownGate::ShutdownGate(): signalReceived(false)
{
    masterConf.read();
}

ShutdownGate::~ShutdownGate(){}

void ShutdownGate::setReceiveGate()
{
    zmq.registerSession(
        masterConf.localhost,
        masterConf.subPort,
        ZmqWrapper::zmqPatternEnum::SUBSCRIBE,
        masterConf.shutdownTopic,
        [this](std::string msg, std::string topic){
            signalReceived = true;
        }
    );
}

void ShutdownGate::setSendGate()
{
    zmq.registerSession(
        masterConf.localhost,
        masterConf.pubPort,
        ZmqWrapper::zmqPatternEnum::PUBLISH,
        masterConf.shutdownTopic
    );
}

bool ShutdownGate::checkSignal()
{
    std::string rmsg = "";
    auto res = zmq.pollMessage(rmsg, 1);
    return signalReceived;
}

void ShutdownGate::sendSignal()
{
    zmq.sendMessage("ok");
}

bool ShutdownGate::isSignalReceived(){
    return signalReceived;
}
