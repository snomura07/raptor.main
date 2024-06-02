#ifndef INCLUDED_CAMERA
#define INCLUDED_CAMERA
#include <opencv2/opencv.hpp>

class Camera
{
public:
    Camera();
    ~Camera();
    int init();
    void capture();
    void save(const std::string& filename);

private:
    bool isDevelop;
    cv::VideoCapture cap;
    cv::Mat frame;
};

#endif
