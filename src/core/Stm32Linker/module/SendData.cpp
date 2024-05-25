#include <iostream>
#include <cstring>
#include "SendData.h"

SendData::SendData(){}

SendData::~SendData(){}

void SendData::clear(){
    memset(buff, 0, sizeof(buff));
    buff[0]           = startByte;
    buff[BUFF_SIZE-1] = endByte;
}

void SendData::create(){
    clear();
    buff[1] = (timerCnt >> 24) & 0xFF;
    buff[2] = (timerCnt >> 16) & 0xFF;
    buff[3] = (timerCnt >> 8 ) & 0xFF;
    buff[4] = (timerCnt >> 0 ) & 0xFF;
}
