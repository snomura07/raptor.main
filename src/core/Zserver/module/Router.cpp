#include "Router.h"

Router::Router(){}

Router::~Router(){}

void Router::setRequestPath(std::string requestPath)
{
    requestPath = requestPath;
}

bool Router::get(std::string routePath)
{
    return routePath == requestPath;
}

bool Router::get(std::string routePath, std::vector<int> params, bool paramRequired)
{
    if(paramRequired && params.size()<1){
        return false;
    }

    return routePath == requestPath;
}
