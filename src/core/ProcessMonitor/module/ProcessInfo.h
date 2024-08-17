#include <string>
#include <vector>
#include <ZmqWrapper/ZmqWrapper.h>

class ProcessInfo{
public:
    ProcessInfo(std::string jsonPath);
    ~ProcessInfo();
    bool isAlive();
    void checkAlive();
    bool isModified();

public:
    std::string modName;
    int healthCheckPort;

private:
    ZmqWrapper zmq;
    bool aliveFlag;
    bool preAliveFlag;
};
