#include "Gateway.h"
#include "Router.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <str.hpp>

Gateway::Gateway()
{
    masterConf.read();
}

Gateway::~Gateway(){}

std::string Gateway::routeRequest(std::string path, std::vector<int> params)
{
    std::string rmsg = "";

    router.setRequestPath(path);
    if(router.get("test")){
        rmsg = "Zserver running now!";
        std::cout << rmsg << std::endl;
    }
    else if(router.get("gpio/chmode/input", params, true)){
        int pinNo = params.front();
        gpioController.chModeInput(pinNo);
    }
    else if(router.get("gpio/chmode/output", params, true)){
        int pinNo = params.front();
        gpioController.chModeOutput(pinNo);
    }
    else if(router.get("gpio/setio/high", params, true)){
        int pinNo = params.front();
        gpioController.setHigh(pinNo);
    }
    else if(router.get("gpio/setio/low", params, true)){
        int pinNo = params.front();
        gpioController.setLow(pinNo);
    }
    else if(router.get("camera/capture/save", params, true)){
        std::string imagePath = masterConf.imagePath + "ttt.png";
        cameraController.save(imagePath);
    }


    else{
        rmsg = "404 Not Found... > " + path;
    }

    return rmsg;
}
