#include <string>
#include <memory>
#include <unordered_map>
#include <RaptorBase/RaptorBase.h>
#include <InfoChat/InfoChat.h>
#include "../config/AppConfig.h"
#include "ConfSummary.h"
#include "ProcessInfo.h"

class ProcessMonitor : public RaptorBase{
public:
    ProcessMonitor();
    ~ProcessMonitor();
    bool run();

private:
    InfoChat infoChat;
    AppConfig config;
    ConfSummary confSummary;
    std::unordered_map<std::string, std::shared_ptr<ProcessInfo>> processMap;
};
