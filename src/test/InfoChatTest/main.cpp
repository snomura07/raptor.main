#include <iostream>
#include <string>
#include <print.hpp>
#include <str.hpp>
#include <msleep.hpp>
#include <InfoChat/InfoChat.h>

int main()
{
    InfoChat infoChat;

    infoChat.sendInfoMsg("InfoChatTest", "hfsfa");

    infoChat.sendErrorMsg("InfoChatTest", "ｇｇっがが");

    infoChat.sendInfoMsg("InfoChatTest", "hfsfa");

    return 0;
}
