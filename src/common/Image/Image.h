#ifndef INCLUDED_IMAGE
#define INCLUDED_IMAGE
#include <string>
#include <memory>
#include <opencv2/opencv.hpp>

class Image{
public:
    Image();
    Image(const std::string& imgFilePath);
    ~Image();
    int width();
    int height();
    int channel();
    int size();
    const unsigned char* data();

public:
    void readFromMat(const cv::Mat &mat);
    void readFromFile(const std::string &imgFilePath);
    void readFromBinary(const std::string &bin);
    void saveAsPng(const std::string &filename);
    std::string encode();
    void decode(const std::string &bin);
    void setTime();

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

#endif
