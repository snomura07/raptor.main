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
    if (!isDevelop) {
        cv::destroyAllWindows();
    }
}

int Camera::open()
{
    if (isDevelop) {
        frame = cv::imread("/home/nomura/image/test.png");
        if (frame.empty()) {
            std::cerr << "Failed to load image" << std::endl;
            return -1;
        }
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
    if (!isDevelop) {
        cap >> frame;
    }
}

void Camera::save(const std::string& filename)
{
    cv::imwrite(filename, frame);
}

std::string Camera::encode()
{
    int width   = frame.cols;
    int height  = frame.rows;
    int channel = frame.channels();
    int size    = width * height * channel;
    std::string data_str(reinterpret_cast<char const*>(frame.data), size);

    return data_str;
}
