#include "Gateway.h"
#include "Router.h"
#include <vector>
#include <regex>
#include <str.hpp>

Gateway::Gateway(){}

Gateway::~Gateway(){}

std::string Gateway::routeRequest(std::string path, std::vector<int> params)
{
    this->router.setRequestPath(path);
    if(router.get("test")){
    }
    else if(router.get("gpio/chmode/input", params, true)){
        int pinNo = params.front();
        this->gpioController.chModeInput(pinNo);
    }
    else if(router.get("gpio/chmode/output", params, true)){
        int pinNo = params.front();
        this->gpioController.chModeOutput(pinNo);
    }
    else if(router.get("gpio/setio/high", params, true)){
        int pinNo = params.front();
        this->gpioController.setHigh(pinNo);
    }
    else if(router.get("gpio/setio/low", params, true)){
        int pinNo = params.front();
        this->gpioController.setLow(pinNo);
    }

    return "";
}
