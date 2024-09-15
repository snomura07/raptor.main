#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

class Zdata {
public:
    Zdata();
    Zdata(const std::string& jsonString);
    ~Zdata();

    void parse(const std::string& jsonString);

public:
    std::string mainCommand;
    std::vector<int> optValue;

private:
    nlohmann::json JsonData;
};
