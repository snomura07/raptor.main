#include <iostream>
#include <zmq.h>
#include <string>
#include <example/example.pb.h>

int main() {
    void* context = zmq_ctx_new();
    void* requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5555");

    raptor::protobuf::Person person;
    person.set_name("tesasasat");
    person.set_id(111);
    person.set_email("john.doe@example.com");
    std::string serialized;
    person.SerializeToString(&serialized);

    zmq_send(requester, serialized.c_str(), serialized.size(), 0);
    std::cout << "Sent message: " << serialized << std::endl;

    char buffer[256];
    zmq_recv(requester, buffer, sizeof(buffer), 0);
    std::string response = buffer;
    std::cout << "Received response: " << response << std::endl;

    zmq_close(requester);
    zmq_ctx_destroy(context);
    return 0;
}
