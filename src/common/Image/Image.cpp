#include "Image.h"
#include <iostream>
#include <cstring>
#include <opencv2/opencv.hpp>

class Image::Impl {
public:
    Impl(const std::string& imgFilePath)
        : width(0), height(0), channel(0), size(0) {
        frame = cv::imread(imgFilePath);
        if (!frame.empty()) {
            width   = frame.cols;
            height  = frame.rows;
            channel = frame.channels();
            size    = width * height * channel;
        } else {
            std::cerr << "Failed to load image: " << imgFilePath << std::endl;
        }
    }

    int width;
    int height;
    int channel;
    int size;
    cv::Mat frame;
};

Image::Image(const std::string& imgFilePath)
    : pImpl(std::make_unique<Impl>(imgFilePath)) {}
Image::~Image() = default;

int Image::width()   { return pImpl->width; }
int Image::height()  { return pImpl->height; }
int Image::channel() { return pImpl->channel; }
int Image::size()    { return pImpl->size; }
const unsigned char* Image::data() { return pImpl->frame.data; }


class ImageMagic::Impl {
public:
    Impl(){}
};
ImageMagic::ImageMagic()
    : pImpl() {}
ImageMagic::~ImageMagic() = default;

void ImageMagic::image2Bytes(Image &image, std::string &bytes)
{
    std::string dataStr(reinterpret_cast<char const*>(image.data()), image.size());
    bytes = dataStr;
}

void ImageMagic::writePng(Image &image, std::string filename)
{
    if (cv::imwrite(filename, frame)) {
        std::cout << "Image saved as " << filename << std::endl;
    }
    else {
        std::cerr << "Failed to save image to " << filename << std::endl;
    }
}
