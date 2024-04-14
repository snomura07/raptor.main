#ifndef INCLUDED_GATEWAY
#define INCLUDED_GATEWAY
#include <string>
#include "Router.h"

class Gateway
{
public:
    Gateway();
    ~Gateway();

    std::string routeRequest(std::string msg);

private:
    Router router;
};

#endif
