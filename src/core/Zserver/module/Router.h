#ifndef INCLUDED_ROUTER
#define INCLUDED_ROUTER
#include <string>
#include <vector>
#include <Gpio/Gpio.h>

class Router
{
public:
    Router();
    ~Router();
    std::string callMethod(std::vector<std::string> &segs);

private:
    Gpio gpio;
};

#endif
