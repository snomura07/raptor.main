#include "Gpio.h"
#include <iostream>
#include <pigpio.h>
#include <env.hpp>

Gpio::Gpio()
{
    this->isDevelop = isDevEnv();
}

Gpio::~Gpio(){
    if(!this->isDevelop){
        gpioTerminate();
    }
}

int Gpio::init(){
    if(this->isDevelop){
        return 0;
    }

    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed" << std::endl;
        return -1;
    }
    return 0;
}

void Gpio::chModeOutput(int pinNo){
    if(!this->isDevelop){
        gpioSetMode(pinNo, PI_OUTPUT);
    }
}

void Gpio::chModeInput(int pinNo){
    if(!this->isDevelop){
        gpioSetMode(pinNo, PI_INPUT);
    }
}

void Gpio::setHigh(int pinNo){
    if(!this->isDevelop){
        gpioWrite(pinNo, 1);
    }
}

void Gpio::setLow(int pinNo){
    if(!this->isDevelop){
        gpioWrite(pinNo, 0);
    }
}
