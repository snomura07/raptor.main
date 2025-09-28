#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ZmqWrapper/ZmqWrapper.h>
#include <MasterConfig/MasterConfig.h>
#include <ShutdownGate/ShutdownGate.h>

int main(int argc, char **argv)
{
    ShutdownGate shutdownGate;
    shutdownGate.setSendGate();

    for(int i=0; i<2; i++){
        shutdownGate.sendSignal();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
