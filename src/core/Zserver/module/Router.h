#ifndef INCLUDED_ROUTER
#define INCLUDED_ROUTER
#include <string>
#include <vector>

class Router
{
public:
    Router();
    ~Router();
    void registRequestPath(std::string requestPath);
    bool get(std::string routePath);
    bool get(std::string routePath, std::vector<int> params, bool paramRequired);

private:
    std::string requestPath;
};

#endif
