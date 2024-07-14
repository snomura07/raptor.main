#include "Gateway.h"
#include "Router.h"
#include <iostream>
#include <vector>
#include <regex>
#include <str.hpp>

Gateway::Gateway(){}

Gateway::~Gateway(){}

std::string Gateway::routeRequest(std::string path, std::vector<int> params)
{
    std::string rmsg = "";

    this->router.setRequestPath(path);
    if(router.get("test")){
        rmsg = "Zserver running now!";
        std::cout << rmsg << std::endl;
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
    else if(router.get("camera/capture/save", params, true)){
        this->cameraController.save("/home/nomura/image/ttt.png");
    }


    else{
        rmsg = "404 Not Found... > " + path;
    }

    return rmsg;
}
