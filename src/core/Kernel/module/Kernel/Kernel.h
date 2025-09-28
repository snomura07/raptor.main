#include <string>
#include <memory>
#include <unordered_map>
#include <RaptorBase/RaptorBase.h>
#include <ShutdownGate/ShutdownGate.h>
#include "../../config/AppConfig.h"
#include "../ConfSummary/ConfSummary.h"
#include "../ProcessInfo/ProcessInfo.h"
#include "../Launcher/Launcher.h"

class Kernel : public RaptorBase{
public:
    Kernel();
    ~Kernel();
    bool run();
    bool launchProcess();
    bool healthCheckProcess();
    bool checkShutdownCommand();
    bool shutdownProcess();

private:
    AppConfig config;
    Launcher launcher;
    ConfSummary confSummary;
    std::unordered_map<std::string, std::shared_ptr<ProcessInfo>> processMap;
    ShutdownGate shutdownGate;
};
