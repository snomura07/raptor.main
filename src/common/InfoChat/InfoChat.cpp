#include <print.hpp>
#include <str.hpp>
#include <msleep.hpp>
#include <ChatServerMsg/ChatServerMsg.pb.h>
#include "InfoChat.h"

InfoChat::InfoChat()
{
    masterConf.read();

    std::string ip    = masterConf.localhost;
    int pubPort       = masterConf.pubPort;
    std::string topic = masterConf.chatTopic;
    zmq.registerSession(ip, pubPort , ZmqWrapper::zmqPatternEnum::PUBLISH, topic);
}

InfoChat::~InfoChat(){}

void InfoChat::sendInfoMsg(std::string modName, std::string msg)
{
    raptor::protobuf::ChatServerMsg chatServerMsg;
    chatServerMsg.set_viewname1(modName);
    chatServerMsg.set_msg(msg);
    chatServerMsg.set_type(raptor::protobuf::ChatServerMsg::INFO);

    std::string sMsg;
    chatServerMsg.SerializeToString(&sMsg);
    zmq.sendMessage(sMsg);
    msleep(10);
}

void InfoChat::sendErrorMsg(std::string modName, std::string msg)
{
    raptor::protobuf::ChatServerMsg chatServerMsg;
    chatServerMsg.set_viewname1(modName);
    chatServerMsg.set_msg(msg);
    chatServerMsg.set_type(raptor::protobuf::ChatServerMsg::ERROR);

    std::string sMsg;
    chatServerMsg.SerializeToString(&sMsg);
    zmq.sendMessage(sMsg);
    msleep(10);
}
