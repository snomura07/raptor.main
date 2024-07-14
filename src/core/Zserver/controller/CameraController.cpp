#include "CameraController.h"

CameraController::CameraController()
{
    this->camera.open();
}

CameraController::~CameraController(){}

void CameraController::save(const std::string& filename){
    this->camera.capture();
    this->camera.save(filename);
}
