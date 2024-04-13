#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <zmq.h>
#include "ZmqWrapper.h"

ZmqWrapper::ZmqWrapper(){}

ZmqWrapper::~ZmqWrapper()
{
    int linger = 0;
    zmq_setsockopt(this->m_socket, ZMQ_LINGER, &linger, sizeof(linger));
    zmq_close(this->m_socket);
    this->m_socket = nullptr;

    zmq_ctx_destroy(this->m_context);
    this->m_context = nullptr;
}

void ZmqWrapper::registerSession(std::string ip, int port, zmqPatternEnum pattern)
{
    std::string address = "tcp://" + ip + ":" + std::to_string(port);

    this->m_context = zmq_ctx_new();
    this->m_socket  = zmq_socket (this->m_context, pattern);

    if(ip == "*"){
        zmq_bind (this->m_socket, address.c_str());
    }
    else{
        zmq_connect(this->m_socket, address.c_str());
    }
}

int ZmqWrapper::pollMessage(std::string &msg, int timeout)
{
    std::vector<zmq_pollitem_t> items;
    {
        zmq_pollitem_t item = { this->m_socket, 0, ZMQ_POLLIN, 0 };
        items.push_back(item);
    }
    auto res = zmq_poll (&items[0], 1, timeout);
    if(res == 0){
        // print("zmq poll error: timeout");
        return -1;
    }
    if(res < 0){
        // print("zmq poll error: unknown");
        return -1;
    }

    if (items[0].revents & ZMQ_POLLIN) {
        long buff_size = 1024;
        std::shared_ptr<char> buff(new char[buff_size], std::default_delete<char[]>());
        int len = zmq_recv(this->m_socket, buff.get(), buff_size, 0);
        if(len > 0) {
            std::shared_ptr<std::string> message(new std::string(buff.get(), len));
            msg = *message;
            // print("size:" + str(len));
        }
    }

    return 0;
}

int ZmqWrapper::sendMessage(std::string msg)
{
    int len = zmq_send(this->m_socket, msg.c_str(), msg.length(), 0);

    return 0;
}
