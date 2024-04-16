#ifndef INCLUDED_GATEWAY
#define INCLUDED_GATEWAY
#include <string>
#include <vector>
#include "Router.h"

class Gateway
{
public:
    Gateway();
    ~Gateway();
    std::string routeRequest(std::string path, std::vector<int> params);

private:
    Router router;
};

#endif
