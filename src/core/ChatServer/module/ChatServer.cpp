#include <iostream>
#include <string>
#include <fstream>
#include <print.hpp>
#include <str.hpp>
#include <nlohmann/json.hpp>
#include <ZmqWrapper/ZmqWrapper.h>
#include <ChatServerMsg/ChatServerMsg.pb.h>
#include "ChatServer.h"

ChatServer::ChatServer()
{
    config.read();

    // base用の設定
    RaptorBase::modName  = config.modName;
    RaptorBase::commPort = config.healthCheckcPort;
    RaptorBase::runKeepAliveServer();
    RaptorBase::showActivatedSign();
    RaptorBase::initLogger();
}

ChatServer::~ChatServer(){}

bool ChatServer::run()
{
    std::string ip    = config.master.localhost;
    int subPort       = config.master.subPort;
    std::string topic = config.master.chatTopic;

    bool isRunning = true;
    ZmqWrapper zmq;
    zmq.registerSession(ip, subPort , ZmqWrapper::zmqPatternEnum::SUBSCRIBE, topic, std::bind(&ChatServer::receiveMsg, this, std::placeholders::_1, std::placeholders::_1));

    while(isRunning){
        std::string msg = "";
        auto res = zmq.pollMessage(msg, -1);
    }

    return isRunning;
}

void ChatServer::receiveMsg(std::string msg, std::string topic)
{
    raptor::protobuf::ChatServerMsg protoMsg;
    protoMsg.ParseFromString(msg);
    // print(protoMsg.viewname1(), protoMsg.type(), protoMsg.msg());

    if(protoMsg.type() == raptor::protobuf::ChatServerMsg::INFO){
        nlohmann::json jsonFmt;
        jsonFmt["message"]  = protoMsg.msg();
        jsonFmt["type"]     = "info";
        std::string jsonStr = jsonFmt.dump();
        std::string res     = apiClient.post("/send", jsonStr);
        // print(res);
    }
    else if(protoMsg.type() == raptor::protobuf::ChatServerMsg::ERROR){
        nlohmann::json jsonFmt;
        jsonFmt["message"]  = protoMsg.msg();
        jsonFmt["type"]     = "error";
        std::string jsonStr = jsonFmt.dump();
        std::string res     = apiClient.post("/send", jsonStr);
        // print(res);
    }
}
