#include "Router.h"

Router::Router(){}

Router::~Router(){}

std::string callMethod(std::vector<std::string> &segs)
{
    if(segs.size() < 2){
        return "{failed}";
    }

    // status
    if(segs[0] == "status"){

        if(segs[1] == "status"){}
        else if(segs[1] == "status"){}
    }
    // gpio
    if(segs[0] == "gpio"){

        if(segs[1] == "status"){}
        else if(segs[1] == "status"){}
    }

    // test
    else if(segs[0] == "test"){

    }


    else{
        return "{Bad Request!}";
    }
}
