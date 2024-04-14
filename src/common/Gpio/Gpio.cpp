#include "Gpio.h"
#include <iostream>
#include <pigpio.h>

Gpio::Gpio(){}

Gpio::~Gpio(){
    gpioTerminate();
}

int Gpio::init(){
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed" << std::endl;
        return -1;
    }
    return 0;
}

void Gpio::chModeOutput(int pinNo){
    gpioSetMode(pinNo, PI_OUTPUT);
}

void Gpio::chModeInput(int pinNo){
    gpioSetMode(pinNo, PI_INPUT);
}

void Gpio::setHigh(int pinNo){
    gpioWrite(pinNo, 1);
}

void Gpio::setLow(int pinNo){
    gpioWrite(pinNo, 0);
}
