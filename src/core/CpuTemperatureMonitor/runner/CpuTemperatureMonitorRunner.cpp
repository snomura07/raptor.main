#include<iostream>
#include "../module/CpuTemperatureMonitor.h"

int main(int argc, char *argv[])
{
    CpuTemperatureMonitor cpuTemperatureMonitor;
    std::cout << "ok" << std::endl;
    cpuTemperatureMonitor.run();
    return 0;
}
