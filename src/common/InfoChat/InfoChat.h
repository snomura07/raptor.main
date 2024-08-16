#ifndef INCLUDED_INFOCHAT
#define INCLUDED_INFOCHAT
#include <string>
#include <MasterConfig/MasterConfig.h>
#include <ApiClient/ApiClient.h>

class InfoChat{
public:
    InfoChat();
    ~InfoChat();
    std::string sendInfoMsg(std::string msg);
    std::string sendErrorMsg(std::string msg);

private:
    MasterConfig masterConf;
    ApiClient apiClient;
};

#endif
