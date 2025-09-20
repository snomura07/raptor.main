#include <string>
#include <RaptorBase/RaptorBase.h>
#include "../config/AppConfig.h"
#include <Gpio/Gpio.h>

class GpioServer : public RaptorBase{
public:
    GpioServer();
    ~GpioServer();
    bool run();
    void receiveMsg(std::string msg, std::string topic);

private:
    AppConfig config;
    unsigned long count;
    Gpio gpio;
};
