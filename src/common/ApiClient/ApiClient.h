#ifndef INCLUDED_APICLIENT
#define INCLUDED_APICLIENT
#include <string>

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include <MasterConfig/MasterConfig.h>

class ApiClient{
public:
    ApiClient();
    ~ApiClient();
    std::string post(std::string path, std::string msg);
    std::string post(std::string endpoint, std::string path, std::string msg);
    std::string get(std::string path, std::string msg);

private:
    MasterConfig masterConf;
};

#endif
