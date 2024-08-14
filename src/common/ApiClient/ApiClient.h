#ifndef INCLUDED_APICLIENT
#define INCLUDED_APICLIENT
#include <string>
#include <httplib.h>
#include <MasterConfig/MasterConfig.h>

class ApiClient{
public:
    ApiClient();
    ~ApiClient();
    std::string post(std::string path, std::string msg);
    std::string get(std::string path, std::string msg);

private:
    MasterConfig masterConf;
};

#endif
