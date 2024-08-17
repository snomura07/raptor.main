#include <string>
#include <RaptorBase/RaptorBase.h>
#include <ApiClient/ApiClient.h>
#include "../config/AppConfig.h"

class ChatServer : public RaptorBase{
public:
    ChatServer();
    ~ChatServer();
    bool run();

private:
    void receiveMsg(std::string msg, std::string topic);

private:
    ApiClient apiClient;
    AppConfig config;
    unsigned long count;
};
