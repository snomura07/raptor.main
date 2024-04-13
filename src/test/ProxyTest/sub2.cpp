#include <iostream>
#include <string>
#include <zmq.h>
#include <cstring>
#include <example/example.pb.h>
#include <ZmqWrapper/ZmqWrapper.h>

int main()
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5555, ZmqWrapper::zmqPatternEnum::SUBSCRIBE, "important");

    while (true) {
        std::string msg = "";
        auto res = zmq.pollMessage(msg, -1);

        raptor::protobuf::Person parsedPerson;
        parsedPerson.ParseFromString(msg);

        std::cout << "Parsed Person:" << std::endl;
        std::cout << "Name: " << parsedPerson.name() << std::endl;
        std::cout << "ID: " << parsedPerson.id() << std::endl;
        std::cout << "Email: " << parsedPerson.email() << std::endl;
    }

    return 0;
}
