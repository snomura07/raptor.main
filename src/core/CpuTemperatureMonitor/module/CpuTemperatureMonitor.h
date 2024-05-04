#include <string>
#include <RaptorBase/RaptorBase.h>
#include "../config/AppConfig.h"

class CpuTemperatureMonitor : public RaptorBase{
public:
    CpuTemperatureMonitor();
    ~CpuTemperatureMonitor();
    bool run();

private:
    AppConfig config;
    std::string tempFilePath;
    double getTemperature();
};
