#ifndef INCLUDED_RAPTORBASE
#define INCLUDED_RAPTORBASE

#include <string>
#include <thread>
#include <ZmqWrapper/ZmqWrapper.h>
#include <Logger/Logger.h>
#include <InfoChat/InfoChat.h>

class RaptorBase {
protected:
    std::string modName;
    int commPort;
    Logger logger;
    InfoChat infoChat;
    bool shutdownCommandReceived;

public:
    RaptorBase();
    ~RaptorBase();
    void init(std::string modName_, int commPort_);
    bool runKeepAliveServer();
    void showActivatedSign();
    void initLogger();
    bool isRunning();

private:
    ZmqWrapper zmq;
    std::thread th;
};

#endif
