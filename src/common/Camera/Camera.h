#ifndef INCLUDED_CAMERA
#define INCLUDED_CAMERA
#include <opencv2/opencv.hpp>
#include <Image/Image.h>

class Camera
{
public:
    using mat = cv::Mat;
    using vc  = cv::VideoCapture;

public:
    Camera();
    ~Camera();
    int open();
    void capture();
    void save(const std::string& filename);
    std::string encode();

private:
    bool isDevelop;
    vc  cap;
    mat frame;
    Image image;
};

#endif
