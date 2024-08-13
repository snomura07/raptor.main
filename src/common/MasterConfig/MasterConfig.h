#ifndef INCLUDED_MASTERCONFIG
#define INCLUDED_MASTERCONFIG

#include <map>
#include <string>
#include <variant>
#include <nlohmann/json.hpp>

class MasterConfig {
public:
    MasterConfig();
    ~MasterConfig();
    void read();

    std::string getStringFromMap(std::string key);
    int getIntFromMap(std::string key);

public:
    std::string localhost;
    std::string raptorIp;
    int subPort;
    int pubPort;
    std::string configPath;
    std::string imagePath;
    std::string cameraPath;
    std::string logPath;

private:
    nlohmann::json jsonData;
    std::string jsonPath;
    std::map<std::string, std::variant<int, std::string>> mapFmt;
};

#endif
