#include <iostream>
//#include "/usr/local/include/pigpio.h"
#include "/usr/local/include/zmq.h"
#include <string>

int main() {
    void* context = zmq_ctx_new();
    void* requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5555");

    std::string message = "hello";
    zmq_send(requester, message.c_str(), message.size(), 0);
    std::cout << "Sent message: " << message << std::endl;

    char buffer[256];
    zmq_recv(requester, buffer, sizeof(buffer), 0);
    std::string response = buffer;
    std::cout << "Received response: " << response << std::endl;

    zmq_close(requester);
    zmq_ctx_destroy(context);
    return 0;
}

