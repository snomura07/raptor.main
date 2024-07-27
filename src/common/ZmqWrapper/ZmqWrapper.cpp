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
    zmq_setsockopt(this->socket, ZMQ_LINGER, &linger, sizeof(linger));
    zmq_close(this->socket);
    this->socket = nullptr;

    zmq_ctx_destroy(this->context);
    this->context = nullptr;
}

void ZmqWrapper::registerSession(std::string ip, int port, zmqPatternEnum pattern, std::string topic)
{
    std::string address = "tcp://" + ip + ":" + std::to_string(port);

    this->context = zmq_ctx_new();
    this->socket  = zmq_socket (this->context, pattern);
    this->topic   = topic;

    if(pattern == SUBSCRIBE){
        zmq_setsockopt(this->socket, ZMQ_SUBSCRIBE, topic.c_str(), topic.length());
    }

    if(ip == "*"){
        zmq_bind (this->socket, address.c_str());
    }
    else{
        zmq_connect(this->socket, address.c_str());
    }
}
void ZmqWrapper::registerSession(std::string ip, int port, zmqPatternEnum pattern, std::string topic, const CallbackFunction& callback)
{
    std::string address = "tcp://" + ip + ":" + std::to_string(port);

    this->context            = zmq_ctx_new();
    this->socket             = zmq_socket (this->context, pattern);
    this->topic              = topic;
    this->callbackMap[topic] = callback;

    if(pattern == SUBSCRIBE){
        zmq_setsockopt(this->socket, ZMQ_SUBSCRIBE, topic.c_str(), topic.length());
    }

    if(ip == "*"){
        zmq_bind (this->socket, address.c_str());
    }
    else{
        zmq_connect(this->socket, address.c_str());
    }
}


int ZmqWrapper::pollMessage(std::string &msg, int timeout)
{
    std::vector<zmq_pollitem_t> items;
    {
        zmq_pollitem_t item = { this->socket, 0, ZMQ_POLLIN, 0 };
        items.push_back(item);
    }
    auto res = zmq_poll (&items[0], 1, timeout);

    // timeout
    if(res == 0){
        return -1;
    }
    // poll error
    if(res < 0){
        return -1;
    }

    if (items[0].revents & ZMQ_POLLIN) {
        long buff_size = 1024;
        std::shared_ptr<char> buff(new char[buff_size], std::default_delete<char[]>());
        zmq_recv(this->socket, buff.get(), buff_size, 0);
        std::string data(buff.get());

        std::string topic = data.substr(0, data.find('$'));
        std::string message_content = data.substr(data.find('$') + 1);
        msg = message_content;

        if (auto it = callbackMap.find(topic); it != callbackMap.end()) {
            it->second(msg, topic);
        } else {
            //Callback function not found for topic
        }
    }

    return 0;
}

int ZmqWrapper::sendMessage(std::string msg)
{
    std::string taggedMsg = this->topic + '$' + msg;
    int len = zmq_send(this->socket, taggedMsg.c_str(), taggedMsg.length(), 0);

    return 0;
}
