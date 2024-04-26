#include <iostream>
#include <string>
#include <zmq.h>
#include <cstring>
#include <example/example.pb.h>
#include <ZmqWrapper/ZmqWrapper.h>

void receiveMsg(std::string msg, std::string topic)
{
    std::cout << topic << " : " << msg << std::endl;
}

int main()
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5555, ZmqWrapper::zmqPatternEnum::SUBSCRIBE, "important", &receiveMsg);

    while (true) {
        std::string msg = "";
        auto res = zmq.pollMessage(msg, 10);
        if(res < 0){
            continue;
        }

        // raptor::protobuf::Person parsedPerson;
        // parsedPerson.ParseFromString(msg);

        // std::cout << "Parsed Person:" << std::endl;
        // std::cout << "Name: " << parsedPerson.name() << std::endl;
        // std::cout << "ID: " << parsedPerson.id() << std::endl;
        // std::cout << "Email: " << parsedPerson.email() << std::endl;
    }

    return 0;
}
