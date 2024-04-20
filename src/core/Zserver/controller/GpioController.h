#ifndef INCLUDED_GPIO_CONTROLLER
#define INCLUDED_GPIO_CONTROLLER
#include <string>
#include <vector>
#include <Gpio/Gpio.h>

class GpioController
{
public:
    GpioController();
    ~GpioController();
    void chModeOutput(int pinNo);
    void chModeInput(int pinNo);
    void setHigh(int pinNo);
    void setLow(int pinNo);

private:
    std::string requestPath;
    Gpio gpio;
};

#endif
