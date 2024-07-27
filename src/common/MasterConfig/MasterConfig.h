#ifndef INCLUDED_MASTERCONFIG
#define INCLUDED_MASTERCONFIG

#include <string>
#include <nlohmann/json.hpp>

class MasterConfig {
public:
    MasterConfig();
    ~MasterConfig();
    void read();

public:
    int subPort;
    int pubPort;
    std::string configPath;

private:
    nlohmann::json jsonData;
    std::string jsonPath;
};

#endif
