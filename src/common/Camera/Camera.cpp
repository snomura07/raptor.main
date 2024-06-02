#include "Camera.h"
#include <iostream>
#include <cstring>
#include <Env/Env.h>
#include <msleep.hpp>
#include <opencv2/opencv.hpp>

Camera::Camera()
{
    this->isDevelop = isDevEnv();

    cv::VideoCapture cap(0); // Open the default camera
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera" << std::endl;
        // Handle error
    }
}


Camera::~Camera()
{
}
