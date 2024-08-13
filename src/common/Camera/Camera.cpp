#include "Camera.h"
#include <iostream>
#include <cstring>
#include <Env/Env.h>
#include <msleep.hpp>
#include <print.hpp>
#include <opencv2/opencv.hpp>

Camera::Camera()
{
    isDevelop = isDevEnv();
    masterConf.read();
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
        std::string imagePath = masterConf.imagePath + "/test.png";
        frame = cv::imread(imagePath);
        if (frame.empty()) {
            std::cerr << "Failed to load image" << std::endl;
            return -1;
        }
        image.readFromMat(frame);
        return 0;
    }

    cap.open(0);
    if (cap.isOpened()) {
        print("Camera successfully opened on index 0");
        cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
        cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
        cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('Y', 'U', 'Y', 'V'));

        print("Frame width:", cap.get(cv::CAP_PROP_FRAME_WIDTH));
        print("Frame height:", cap.get(cv::CAP_PROP_FRAME_HEIGHT));
        print("FourCC:", cap.get(cv::CAP_PROP_FOURCC));
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
            image.readFromMat(frame);
        }
        else {
            std::cerr << "Failed to capture frame" << std::endl;
        }
    }
}

void Camera::save(const std::string& filename)
{
    image.setTime();
    image.saveAsPng(filename);
}

std::string Camera::encode()
{
    return image.encode();
}
