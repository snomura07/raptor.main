#include <iostream>
#include <string>
#include <zmq.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <example/example.pb.h>

int main()
{
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUB);
    zmq_connect(publisher, "tcp://localhost:5556");

    while (true) {
        // メッセージとトピックを連結して送信
        std::string topic = "important";
        std::string message = "This is some important data";
        raptor::protobuf::Person person;
        person.set_name("tesasasat");
        person.set_id(111);
        person.set_email("john.doe@example.com");
        std::string serialized;
        person.SerializeToString(&serialized);

        std::string tagged_message = topic + " " + serialized;
        zmq_send(publisher, tagged_message.c_str(), tagged_message.size(), 0);

        // 一定時間待機
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    zmq_close(publisher);
    zmq_ctx_destroy(context);

    return 0;
}
