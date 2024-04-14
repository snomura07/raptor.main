#ifndef INCLUDED_GPIO
#define INCLUDED_GPIO

#include <string>

class Gpio
{
public:
    Gpio();
    ~Gpio();

    int init();
    void chModeOutput(int pinNo);
    void chModeInput(int pinNo);
    void setHigh(int pinNo);
    void setLow(int pinNo);
};

#endif
