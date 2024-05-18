#include <iostream>
#include <Gpio/Gpio.h>
#include <msleep.hpp>

int main() {
    Gpio gpio;
    if(gpio.init() < 0){
        std::cout << "Gpio init error!" << std::endl;
        return 0;
    }

    if(gpio.openSerialDevice(115200) < 0){
        std::cout << "Serial open error!" << std::endl;
        return 0;
    }

    while (true) {
        char bytes[10];
        int size = gpio.serialRead(bytes, 10);
        if (size > 1) {
            std::cout << "Received data: ";
            for (int i = 0; i < 10; ++i) {
                std::cout << std::hex << static_cast<int>(bytes[i]) << " ";
            }
            std::cout << std::endl;
        }
        msleep(10);
    }


    return 0;
}
