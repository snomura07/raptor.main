#ifndef INCLUDED_CAMERA_CONTROLLER
#define INCLUDED_CAMERA_CONTROLLER
#include <string>
#include <vector>
#include <Camera/Camera.h>

class CameraController
{
public:
    CameraController();
    ~CameraController();
    void save(const std::string& filename);

private:
    Camera camera;
};

#endif
