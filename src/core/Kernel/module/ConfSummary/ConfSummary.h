#include <string>
#include <vector>
#include <MasterConfig/MasterConfig.h>

class ConfSummary{
public:
    ConfSummary();
    ~ConfSummary();
    void show();

public:
    std::vector<std::string> jsonList;

private:
    MasterConfig masterConf;
};
