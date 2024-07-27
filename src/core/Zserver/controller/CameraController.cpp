#include "CameraController.h"

CameraController::CameraController()
{
    camera.open();
}

CameraController::~CameraController(){}

void CameraController::save(const std::string& filename){
    camera.capture();
    camera.save(filename);
}
