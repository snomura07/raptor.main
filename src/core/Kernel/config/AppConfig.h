#ifndef INCLUDED_KERNEL_APPCONF
#define INCLUDED_KERNEL_APPCONF

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <MasterConfig/MasterConfig.h>

class AppConfig{
public:
    AppConfig();
    ~AppConfig();
    void read();
    void dump();

public:
    struct Process{
        std::string mod;
        bool launch;
    };

    std::string modName;
    int healthCheckPort;
    MasterConfig master;
    std::vector<Process> LaunchProcesses;

private:
    nlohmann::json jsonData;
    std::string jsonPath;
};

#endif
