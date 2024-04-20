#include "Router.h"

Router::Router(){}

Router::~Router(){}

void Router::registRequestPath(std::string requestPath)
{
    this->requestPath = requestPath;
}

bool Router::get(std::string routePath)
{
    return routePath == this->requestPath;
}

bool Router::get(std::string routePath, std::vector<int> params, bool paramRequired)
{
    if(paramRequired && params.size()<1){
        return false;
    }

    return routePath == this->requestPath;
}
