#include <string>
#include <RaptorBase/RaptorBase.h>
#include "../config/AppConfig.h"

class ChatServer : public RaptorBase{
public:
    ChatServer();
    ~ChatServer();
    bool run();

private:
    AppConfig config;
    unsigned long count;
};
