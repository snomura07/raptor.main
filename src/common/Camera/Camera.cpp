#include "Camera.h"
#include <iostream>
#include <cstring>
#include <Env/Env.h>
#include <msleep.hpp>
#include <opencv2/opencv.hpp>

Camera::Camera()
{
    isDevelop = isDevEnv();
}

Camera::~Camera()
{
    cap.release();
    cv::destroyAllWindows();
}

int Camera::init()
{
    if (isDevelop) {
        return 0;
    }

    cap.open(0);
    if (!cap.isOpened()) {
        std::cerr << "Failed to open camera" << std::endl;
        return -1;
    }

    return 0;
}

void Camera::capture()
{
    cap >> frame;
}

void Camera::save(const std::string& filename)
{
    cv::imwrite(filename, frame);
}
