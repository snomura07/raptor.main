#include <iostream>
#include <zmq.h>
#include <string>
#include <example/example.pb.h>

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
        raptor::protobuf::Person parsed_person;
        parsed_person.ParseFromString(request);

        std::cout << "Received request" << std::endl;
        std::cout << "Parsed Person:" << std::endl;
        std::cout << "Name: " << parsed_person.name() << std::endl;
        std::cout << "ID: " << parsed_person.id() << std::endl;
        std::cout << "Email: " << parsed_person.email() << std::endl;

        // Send the response
        zmq_send(responder, request.c_str(), request.size(), 0);
    }

    zmq_close(responder);
    zmq_ctx_destroy(context);
    return 0;
}
