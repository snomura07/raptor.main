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

    char data_to_send[10] = {0xBB, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x66};
    uint32_t timerCnt = 0;
    while(1){
        data_to_send[1] = (timerCnt >> 24) & 0xFF;
        data_to_send[2] = (timerCnt >> 16) & 0xFF;
        data_to_send[3] = (timerCnt >> 8 ) & 0xFF;
        data_to_send[4] = (timerCnt >> 0 ) & 0xFF;

        gpio.serialWrite(data_to_send, 10);
        timerCnt++;
        msleep(1);
    }

    return 0;
}
