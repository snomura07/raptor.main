#include <iostream>
#include <cstring>
#include <Gpio/Gpio.h>
#include <msleep.hpp>
#define BUFF_SIZE 50

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

    char send_buff[BUFF_SIZE];
    char read_buff[BUFF_SIZE];
    uint32_t timerCnt = 0;
    while (true) {
        // send
        memset(send_buff, 0, sizeof(send_buff));
        send_buff[0]           = 0xBB;
        send_buff[BUFF_SIZE-1] = 0x66;

        send_buff[1] = (timerCnt >> 24) & 0xFF;
        send_buff[2] = (timerCnt >> 16) & 0xFF;
        send_buff[3] = (timerCnt >> 8 ) & 0xFF;
        send_buff[4] = (timerCnt >> 0 ) & 0xFF;
        gpio.serialWrite(send_buff, BUFF_SIZE);
        timerCnt++;

        // read
        int size = gpio.serialRead(read_buff, BUFF_SIZE);
        if (size > 1) {
            std::cout << "Received data: ";
            for (int i = 0; i < BUFF_SIZE; ++i) {
                std::cout << std::hex << static_cast<int>(read_buff[i]) << " ";
            }
            std::cout << std::endl;
        }
        msleep(10);
    }


    return 0;
}
