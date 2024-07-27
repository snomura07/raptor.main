#include "Gpio.h"
#include <iostream>
#include <cstring>
#include <pigpio.h>
#include <Env/Env.h>
#include <msleep.hpp>

Gpio::Gpio()
{
    isDevelop = isDevEnv();
    serialHandle = 0;
}

Gpio::~Gpio(){
    if(!isDevelop){
        // serial terminate
        if(serialHandle != 0){
            std::cerr << "close serial port" << std::endl;
            serClose(serialHandle);
        }

        gpioTerminate();
    }
}

int Gpio::init(){
    if(isDevelop){
        return 0;
    }

    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed" << std::endl;
        return -1;
    }
    return 0;
}

void Gpio::chModeOutput(int pinNo){
    if(!isDevelop){
        gpioSetMode(pinNo, PI_OUTPUT);
    }
}

void Gpio::chModeInput(int pinNo){
    if(!isDevelop){
        gpioSetMode(pinNo, PI_INPUT);
    }
}

void Gpio::setHigh(int pinNo){
    if(!isDevelop){
        gpioWrite(pinNo, 1);
    }
}

void Gpio::setLow(int pinNo){
    if(!isDevelop){
        gpioWrite(pinNo, 0);
    }
}

int Gpio::openSerialDevice(int baudRate){
    if(isDevelop){
        return 0;
    }

    serialHandle = serOpen(UDEV, baudRate, 0);
    if (serialHandle < 0) {
        std::cerr << "Unable to open serial device" << std::endl;
        return -1;
    }

    return 1;
}

int Gpio::serialRead(char *bytes, int readSize){
    if(!isDevelop){
        return serRead(serialHandle, bytes, readSize);
    }
}

int Gpio::serialRead1Byte(char &data){
    int res = serRead(serialHandle, &data, 1);
    return res;
}


void Gpio::serialWrite(char *bytes, int size){
    if(!isDevelop){
        serWrite(serialHandle, bytes, size);
    }
}
