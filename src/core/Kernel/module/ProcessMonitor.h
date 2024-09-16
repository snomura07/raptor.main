
#include <InfoChat/InfoChat.h>
#include "ConfSummary.h"
#include "ProcessInfo.h"
#include "../config/AppConfig.h"

class ProcessMonitor{
public:
    ProcessMonitor();
    ~ProcessMonitor();

    void healthCheck();

private:
    AppConfig config;
    InfoChat infoChat;
    ConfSummary confSummary;
    std::unordered_map<std::string, std::shared_ptr<ProcessInfo>> processMap;

};