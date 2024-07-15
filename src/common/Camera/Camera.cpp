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
    if (cap.isOpened()) {
        std::cout << "Camera successfully opened on index 0" << std::endl;
        cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
        cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('Y', 'U', 'Y', 'V'));

        std::cout << "Frame width: " << cap.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
        std::cout << "Frame height: " << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
        std::cout << "FourCC: " << cap.get(cv::CAP_PROP_FOURCC) << std::endl;
    }
    else {
        std::cerr << "Failed to open camera" << std::endl;
        return -1;
    }

    return 0;
}

void Camera::capture()
{
    if (!isDevelop) {
        cap >> frame;
        if (!frame.empty()) {
            std::cout << "Frame captured successfully" << std::endl;
        }
        else {
            std::cerr << "Failed to capture frame" << std::endl;
        }
    }
}

void Camera::save(const std::string& filename)
{
    if (cv::imwrite(filename, frame)) {
        std::cout << "Image saved as " << filename << std::endl;
    }
    else {
        std::cerr << "Failed to save image to " << filename << std::endl;
    }
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
