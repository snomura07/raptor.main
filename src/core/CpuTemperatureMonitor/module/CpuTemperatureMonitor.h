#include <string>

class CpuTemperatureMonitor{
public:
    CpuTemperatureMonitor();
    ~CpuTemperatureMonitor();
    bool run();

private:
    std::string tempFilePath;
    double getTemperature();
};
