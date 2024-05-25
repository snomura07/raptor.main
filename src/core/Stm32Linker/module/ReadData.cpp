#include <iostream>
#include "ReadData.h"

ReadData::ReadData(){}

ReadData::~ReadData(){}

void ReadData::parse(){
    timerCnt = 0;
    timerCnt |= (buff[1] << 24);
    timerCnt |= (buff[2] << 16);
    timerCnt |= (buff[3] << 8);
    timerCnt |= (buff[4] << 0);
}

void ReadData::dump(){
    std::cout << "Received data: ";
    for (int i = 0; i < BUFF_SIZE; ++i) {
        std::cout << std::hex << static_cast<int>(buff[i]) << " ";
    }
    std::cout << std::endl;
}
