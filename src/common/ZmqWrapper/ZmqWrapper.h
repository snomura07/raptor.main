#ifndef INCLUDED_ZMQWRAPPER
#define INCLUDED_ZMQWRAPPER

#include <string>
#include <zmq.h>

class ZmqWrapper
{
public:
    enum zmqPatternEnum{
        REQUEST = ZMQ_REQ,
        REPLY   = ZMQ_REP,
        SUBSCRIBE = ZMQ_SUB,
        PUBLISH = ZMQ_PUB
    };

public:
    ZmqWrapper();
    ~ZmqWrapper();

    void registerSession(std::string ip,
                         int port,
                         zmqPatternEnum pattern,
                         std::string topic);

    int pollMessage(std::string &msg, int timeout);

    int sendMessage(std::string msg);

    void* context;
    void* socket;
    std::string topic;
};

#endif
