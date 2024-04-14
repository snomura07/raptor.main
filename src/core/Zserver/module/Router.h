#ifndef INCLUDED_ROUTER
#define INCLUDED_ROUTER
#include <string>
#include <vector>


class Router
{
public:
    Router();
    ~Router();

    std::string callMethod(std::vector<std::string> &segs);

};

#endif
