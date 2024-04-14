#include "Gateway.h"
#include "Router.h"
#include <vector>
#include <str.hpp>

Gateway::Gateway(){}

Gateway::~Gateway(){}

std::string Gateway::routeRequest(std::string msg)
{
    std::vector<std::string> segments;
    split(msg, "/", segments);

    auto res = this->router.callMethod(segments);
}
