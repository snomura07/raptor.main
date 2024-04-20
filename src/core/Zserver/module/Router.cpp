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
