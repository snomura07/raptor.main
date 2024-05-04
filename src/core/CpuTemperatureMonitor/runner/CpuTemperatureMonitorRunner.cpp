#include<iostream>
#include "../module/CpuTemperatureMonitor.h"

int main(int argc, char *argv[])
{
    CpuTemperatureMonitor cpuTemperatureMonitor;
    cpuTemperatureMonitor.run();
    return 0;
}
