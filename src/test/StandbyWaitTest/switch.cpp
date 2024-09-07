#include <iostream>
#include <string>
#include <ZmqWrapper/ZmqWrapper.h>
#include <msleep.hpp>

int main(int argc, char **argv)
{
    ZmqWrapper zswitch;
    zswitch.registerSession("127.0.0.1", 5555, ZmqWrapper::zmqPatternEnum::SUBSCRIBE, "ZSWITCH", 
        [](std::string msg, std::string topic) {
            std::cout << topic << " : " << msg << std::endl;
        }
    );
    std::string msg = "";
    auto res = zswitch.pollMessage(msg, -1);

    return 0;
}
