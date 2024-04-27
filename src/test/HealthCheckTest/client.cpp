#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ZmqWrapper/ZmqWrapper.h>

int main(int argc, char **argv)
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5590, ZmqWrapper::zmqPatternEnum::REQUEST, "HELTHCHECK");

    std::string msg = "ggg";
    for(int i=0; i<10; i++){
        zmq.sendMessage(msg);

        std::string rmsg = "";
        auto res = zmq.pollMessage(rmsg, 10);
        if(res < 0){
            std::cout << " isDead!!!!!!!!!!!!!!! " << rmsg << std::endl;
        }
        std::cout << i << " : " << rmsg << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
