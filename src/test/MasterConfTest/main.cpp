#include <iostream>
#include <string>
#include <MasterConfig/MasterConfig.h>
#include <print.hpp>

int main() {
    MasterConfig masterConf;
    masterConf.read();

    print(masterConf.raptorIp);
    print(masterConf.getStringFromMap("raptorIp"));
    print(masterConf.getStringFromMap("localhost"));

    return 0;
}
