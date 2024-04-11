#include <iostream>
#include <zmq.h>
#include <string>

int main()
{
    void* context = zmq_ctx_new();
    void* responder = zmq_socket(context, ZMQ_REP);
    zmq_bind(responder, "tcp://*:5555");

    std::cout << "Server started, waiting for messages..." << std::endl;

    while (true) {
        char buffer[256];
        zmq_recv(responder, buffer, sizeof(buffer), 0);
        std::string request = buffer;
        std::cout << "Received request: " << request << std::endl;

        // Send the response
        zmq_send(responder, request.c_str(), request.size(), 0);
    }

    zmq_close(responder);
    zmq_ctx_destroy(context);
    return 0;
}
