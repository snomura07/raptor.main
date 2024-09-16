#include <string>
#include <memory>
#include <unordered_map>
#include <RaptorBase/RaptorBase.h>
#include "../config/AppConfig.h"
#include "Launcher.h"
#include "ProcessMonitor.h"

class Kernel : public RaptorBase{
public:
    Kernel();
    ~Kernel();
    bool run();
    bool launchProcess();
    // CPU, メモリなど資源管理

private:
    AppConfig config;
    Launcher launcher;
    ProcessMonitor processMonitor;
};
