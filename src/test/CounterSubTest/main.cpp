#include <iostream>
#include <string>
#include <zmq.h>
#include <cstring>
#include <CounterMsg/CounterMsg.pb.h>
#include <ZmqWrapper/ZmqWrapper.h>

void receiveMsg(std::string msg, std::string topic)
{
    std::cout << topic << ": " << msg << std::endl;
}

int main()
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5555, ZmqWrapper::zmqPatternEnum::SUBSCRIBE, "COUNTER", &receiveMsg);

    while (true) {
        std::string msg = "";
        auto res = zmq.pollMessage(msg, 100);
        if(res < 0){
            continue;
        }

        raptor::protobuf::CounterMsg counterMsg;
        counterMsg.ParseFromString(msg);

        std::cout << "Name: " << counterMsg.viewname1() << std::endl;
        std::cout << "Count: " << counterMsg.counter() << std::endl;
    }

    return 0;
}
