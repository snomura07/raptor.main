#include <iostream>
#include "Stm32Linker.h"
#include <msleep.hpp>

Stm32Linker::Stm32Linker()
{
    config.read();

    // base用の設定
    modName  = config.modName;
    commPort = config.healthCheckcPort;
    runKeepAliveServer();

    showActivatedSign();
}

Stm32Linker::~Stm32Linker(){}

int Stm32Linker::init()
{
    if(gpio.init() < 0){
        std::cerr << modName << ": Gpio init error!" << std::endl;
        return 0;
    }

    if(gpio.openSerialDevice(115200) < 0){
        std::cerr << modName << ": Serial open error!" << std::endl;
        return 0;
    }

    return 1;
}


bool Stm32Linker::run()
{
    unsigned long timerCnt = 0;
    while (true) {
        // send
        sendData.timerCnt = timerCnt;
        sendData.create();
        gpio.serialWrite(sendData.buff, sendData.BUFF_SIZE);

        // read
        int size = gpio.serialRead(readData.buff, readData.BUFF_SIZE);
        if (size > 1) {
            readData.parse();
            std::cout << "timerCnt: " << readData.timerCnt << std::endl;
        }

        msleep(10);
        timerCnt++;
    }

}
