#ifndef INCLUDED_ZMQWRAPPER
#define INCLUDED_ZMQWRAPPER

#include <string>
#include <zmq.h>

class ZmqWrapper
{
public:
    enum zmqPatternEnum{
        REQUEST = ZMQ_REQ,
        REPLY   = ZMQ_REP
    };

public:
    ZmqWrapper();
    ~ZmqWrapper();

    void registerSession(std::string ip, int port, zmqPatternEnum pattern);

    int pollMessage(std::string &msg, int timeout);

    int sendMessage(std::string msg);

    void* m_context;
    void* m_socket;
};

#endif
