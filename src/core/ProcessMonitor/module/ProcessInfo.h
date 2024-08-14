#include <string>
#include <vector>
#include <ZmqWrapper/ZmqWrapper.h>

class ProcessInfo{
public:
    ProcessInfo(std::string jsonPath);
    ~ProcessInfo();
    bool isActive();
    void checkAlive();

public:
    std::string modName;
    int healthCheckPort;

private:
    bool activeFlag;
};
