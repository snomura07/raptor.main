#include <iostream>
#include <string>
#include <zmq.h>
#include <unistd.h>
#include <thread>
#include <chrono>
#include <example/example.pb.h>
#include <ZmqWrapper/ZmqWrapper.h>

int main()
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5556, ZmqWrapper::zmqPatternEnum::PUBLISH, "PROXTEST");

    while (true) {
        raptor::protobuf::Person person;
        person.set_name("tesasasat");
        person.set_id(111);
        person.set_email("john.doe@example.com");
        std::string serialized;
        person.SerializeToString(&serialized);

        zmq.sendMessage(serialized);

        std::cout << "test" << std::endl;

        // 一定時間待機
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
