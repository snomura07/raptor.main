#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ZmqWrapper/ZmqWrapper.h>
#include <example/example.pb.h>

int main(int argc, char **argv)
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5555, ZmqWrapper::zmqPatternEnum::REQUEST, "TEST");

    std::string msg = "{1,2,3,4,5,6,7777}";
    for(int i=0; i<10; i++){
        zmq.sendMessage(msg);

        std::string rmsg = "";
        auto res = zmq.pollMessage(rmsg, -1);
        std::cout << i << " : " << rmsg << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
