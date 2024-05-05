#include <string>
#include <RaptorBase/RaptorBase.h>
#include <Gpio/Gpio.h>

class Stm32Linker{
public:
    Stm32Linker();
    ~Stm32Linker();
    bool run();

private:
    Gpio gpio;
};
