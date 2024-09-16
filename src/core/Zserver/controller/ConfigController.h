
#ifndef INCLUDED_CONFIG_CONTROLLER
#define INCLUDED_CONFIG_CONTROLLER

#include <string>
#include <MasterConfig/MasterConfig.h>

class ConfigController {
public:
    ConfigController();
    ~ConfigController();
    std::string getConfig(const std::string& configName);
    std::string getList();

private:
    MasterConfig masterConfig;
};

#endif
