#include <iostream>
#include <string>
#include <ZmqWrapper/ZmqWrapper.h>
#include <msleep.hpp>

int main(int argc, char **argv)
{
    ZmqWrapper zmq;
    zmq.registerSession("127.0.0.1", 5556, ZmqWrapper::zmqPatternEnum::PUBLISH, "ZSWITCH");

    for(int i=0; i<100; i++){
        zmq.sendMessage("on");
        msleep(100);
    }

    return 0;
}
