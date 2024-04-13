#include <iostream>
#include <string>
#include <zmq.h>
#include <cstring>
#include <example/example.pb.h>
int main()
{
    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    std::string topic_filter = "important";
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, topic_filter.c_str(), topic_filter.length());
    zmq_connect(subscriber, "tcp://localhost:5555");


    while (true) {
        char buffer[256];
        zmq_recv(subscriber, buffer, sizeof(buffer), 0);

        std::string data(buffer);

        // トピックとメッセージを分割
        std::string topic = data.substr(0, data.find(' '));
        std::string message_content = data.substr(data.find(' ') + 1);
        raptor::protobuf::Person parsed_person;
        parsed_person.ParseFromString(message_content);

        std::cout << "Received Topic: " << topic << std::endl;
        std::cout << "Parsed Person:" << std::endl;
        std::cout << "Name: " << parsed_person.name() << std::endl;
        std::cout << "ID: " << parsed_person.id() << std::endl;
        std::cout << "Email: " << parsed_person.email() << std::endl;
    }

    zmq_close(subscriber);
    zmq_ctx_destroy(context);

    return 0;
}
