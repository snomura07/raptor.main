#include "Router.h"

Router::Router(){
    this->gpio.init();
}

Router::~Router(){}

std::string Router::callMethod(std::vector<std::string> &segs)
{
    if(segs.size() < 2){
        return "{failed}";
    }

    // gpio
    // if (seg == "gpio/chmode/input/{pinNo}")
    // if (seg == "gpio/chmode/output/{pinNo}")
    // if (seg == "gpio/setio/high/{pinNo}")
    // if (seg == "gpio/setio/low/{pinNo}")
    if(segs[0] == "gpio"){
        if(segs[1] == "chmode"){
            if(segs[2] == "input"){
                this->gpio.chModeInput(stoi(segs[3]));
            }
            else if(segs[2] == "output"){
                this->gpio.chModeOutput(stoi(segs[3]));
            }
        }
        else if(segs[1] == "setio"){
            if(segs[2] == "high"){
                this->gpio.setHigh(stoi(segs[3]));
            }
            else if(segs[2] == "low"){
                this->gpio.setLow(stoi(segs[3]));
            }
        }
    }

    // test
    else if(segs[0] == "test"){

    }


    else{
        return "{Bad Request!}";
    }
}
