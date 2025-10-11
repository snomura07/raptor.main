#include <string>
#include <vector>
#include <ZmqWrapper/ZmqWrapper.h>

class ProcessInfo{
public:
    enum State{
        RUNNING,
        STOPPED
    };

public:
    ProcessInfo(std::string jsonPath);
    ~ProcessInfo();
    void init();
    bool isAlive();
    void checkAlive();
    bool isModified();
    void shutdown();

public:
    std::string modName;
    int healthCheckPort;
    State state;

private:
    ZmqWrapper zmq;
    bool aliveFlag;
    bool preAliveFlag;

};
