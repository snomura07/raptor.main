#ifndef INCLUDED_GATEWAY
#define INCLUDED_GATEWAY
#include <string>
#include <vector>
#include "Router.h"
#include "../controller/GpioController.h"
#include "../controller/CameraController.h"

class Gateway
{
public:
    Gateway();
    ~Gateway();
    std::string routeRequest(std::string path, std::vector<int> params);

private:
    Router router;
    GpioController gpioController;
    CameraController cameraController;
};

#endif
