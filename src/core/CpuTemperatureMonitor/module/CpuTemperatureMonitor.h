#include <string>
#include <RaptorBase/RaptorBase.h>

class CpuTemperatureMonitor : public RaptorBase{
public:
    CpuTemperatureMonitor();
    ~CpuTemperatureMonitor();
    bool run();

private:
    std::string tempFilePath;
    double getTemperature();
};
