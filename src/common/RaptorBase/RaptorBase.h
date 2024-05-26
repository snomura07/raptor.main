#ifndef INCLUDED_RAPTORBASE
#define INCLUDED_RAPTORBASE

#include <string>
#include <ZmqWrapper/ZmqWrapper.h>

class RaptorBase {
protected:
    std::string modName;
    int commPort;

public:
    RaptorBase();
    ~RaptorBase();
    bool runKeepAliveServer();
    void showActivatedSign();

private:
    ZmqWrapper zmq;
};

#endif
