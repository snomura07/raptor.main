#include <iostream>
#include "Stm32Linker.h"

Stm32Linker::Stm32Linker()
{
    this->config.read();

    // base用の設定
    this->modName  = this->config.modName;
    this->commPort = this->config.healthCheckcPort;
    this->runKeepAliveServer();

}

Stm32Linker::~Stm32Linker(){}

int Stm32Linker::init()
{
    if(gpio.init() < 0){
        std::cerr << this->modName << ": Gpio init error!" << std::endl;
        return 0;
    }

    if(gpio.openSerialDevice(115200) < 0){
        std::cerr << this->modName << ": Serial open error!" << std::endl;
        return 0;
    }
}


bool Stm32Linker::run()
{

}
