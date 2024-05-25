#include <string>
#include <RaptorBase/RaptorBase.h>
#include <Gpio/Gpio.h>
#include "../config/AppConfig.h"
#include "SendData.h"
#include "ReadData.h"

class Stm32Linker : public RaptorBase{
public:
    Stm32Linker();
    ~Stm32Linker();
    int init();
    bool run();

private:
    Gpio gpio;
    AppConfig config;
    SendData sendData;
    ReadData readData;

};
