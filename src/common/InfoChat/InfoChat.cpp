#include <print.hpp>
#include <str.hpp>
#include "InfoChat.h"

InfoChat::InfoChat()
{
    masterConf.read();
}

InfoChat::~InfoChat(){}

std::string InfoChat::sendInfoMsg(std::string msg)
{
    std::string jsonFmt = strJoin(
        R"({"message": ")",
        msg,
        R"(", "type": "info"})"
    );

    return apiClient.post("/send", jsonFmt);
}
