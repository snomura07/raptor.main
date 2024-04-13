#include <iostream>
#include <string>
#include <ZmqWrapper/ZmqWrapper.h>
#include <example/example.pb.h>

int main(int argc, char **argv)
{
    ZmqWrapper zmq;
    zmq.registerSession("*", 5555, ZmqWrapper::zmqPatternEnum::REPLY);

    for(int i=0; i<10; i++){
        std::string msg = "";
        auto res = zmq.pollMessage(msg, -1);
        std::cout << i << " : " << msg << std::endl;

        zmq.sendMessage("OK!");
    }

    return 0;
}
