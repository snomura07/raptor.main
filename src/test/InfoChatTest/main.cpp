#include <iostream>
#include <string>
#include <print.hpp>
#include <str.hpp>
#include <InfoChat/InfoChat.h>

int main()
{
    InfoChat infoChat;
    print(infoChat.sendInfoMsg("hfsfa"));
    print(infoChat.sendErrorMsg("ｇｇっがが"));

    return 0;
}
