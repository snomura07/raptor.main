#include <string>
#include <nlohmann/json.hpp>

class AppConfig{
public:
    AppConfig();
    ~AppConfig();
    void read();
    void dump();

public:
    std::string modName;
    int healthCheckcPort;
    std::string publishTopic;

private:
    nlohmann::json jsonData;
    std::string jsonPath;
};