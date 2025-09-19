#include <pigpio.h>
#include <iostream>
#include <Gpio/Gpio.h>

int main() {
    Gpio gpio;
    if(gpio.init() < 0){
        std::cout << "Gpio init error!" << std::endl;
        return 0;
    }

    gpio.chModeOutput(23);
    gpio.setHigh(23);

    return 0;
}
