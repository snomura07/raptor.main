#include <iostream>
#include <Gpio/Gpio.h>
#include <msleep.hpp>

int main() {
    Gpio gpio;
    if(gpio.init() < 0){
        std::cout << "Gpio init error!" << std::endl;
        return 0;
    }

    if(gpio.openSerialDevice(38400) < 0){
        std::cout << "Serial open error!" << std::endl;
        return 0;
    }

    while(1){
        gpio.serialWrite("serial test \r\n");
        msleep(100);
    }

    return 0;
}
