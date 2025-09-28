#ifndef INCLUDED_CTRLSHUTDOWN
#define INCLUDED_CTRLSHUTDOWN
#include <string>
#include <MasterConfig/MasterConfig.h>
#include <ZmqWrapper/ZmqWrapper.h>

class ShutdownGate{
public:
    ShutdownGate();
    ~ShutdownGate();
    // receive
    void setReceiveGate();
    bool checkSignal();
    bool isSignalReceived();

    // send
    void setSendGate();
    void sendSignal();

private:
    ZmqWrapper zmq;
    MasterConfig masterConf;
    bool signalReceived;
};

#endif
