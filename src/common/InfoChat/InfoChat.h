#ifndef INCLUDED_INFOCHAT
#define INCLUDED_INFOCHAT
#include <string>
#include <MasterConfig/MasterConfig.h>
#include <ZmqWrapper/ZmqWrapper.h>

class InfoChat{
public:
    InfoChat();
    ~InfoChat();
    void sendInfoMsg(std::string modName, std::string msg);
    void sendErrorMsg(std::string modName, std::string msg);

private:
    ZmqWrapper zmq;
    MasterConfig masterConf;
};

#endif
