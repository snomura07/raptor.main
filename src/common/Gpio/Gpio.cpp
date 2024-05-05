#include "Gpio.h"
#include <iostream>
#include <cstring>
#include <pigpio.h>
#include <env.hpp>
#include <msleep.hpp>

Gpio::Gpio()
{
    this->isDevelop = isDevEnv();
    this->serialHandle = 0;
}

Gpio::~Gpio(){
    if(!this->isDevelop){
        // serial terminate
        if(this->serialHandle != 0){
            std::cerr << "close serial port" << std::endl;
            serClose(this->serialHandle);
        }

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

int Gpio::openSerialDevice(int baudRate){
    this->serialHandle = serOpen(UDEV, baudRate, 0);
    if (this->serialHandle < 0) {
        std::cerr << "Unable to open serial device" << std::endl;
        return -1;
    }

    return 1;
}

void Gpio::serialRead(){
    while (true) {
        // char data;
        // int result = serRead(this->serialHandle, &data, 1);
        char data = 0;
        int res   = this->serialRead1Byte(data);
        if(data == 0xAA){
            std::cout << "find start bit!" << std::endl;
        }
        if(data == 0x55){
            std::cout << "find end bit!" << std::endl;
        }
        std::cout << "res:" << res << " " << data << std::endl;
    }
}

int Gpio::serialRead1Byte(char &data){
    int res = serRead(this->serialHandle, &data, 1);
    return res;
}


void Gpio::serialWrite(std::string msg){
    serWrite(this->serialHandle, const_cast<char*>(msg.c_str()), msg.length());
}
