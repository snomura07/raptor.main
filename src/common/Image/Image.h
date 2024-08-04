#ifndef INCLUDED_IMAGE
#define INCLUDED_IMAGE
#include <string>
#include <memory>

class Image {
public:
    Image(const std::string& imgFilePath);
    ~Image();
    int width();
    int height();
    int channel();
    int size();
    const unsigned char* data();
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

class ImageMagic {
public:
    ImageMagic();
    ~ImageMagic();
    void image2Bytes(Image &image, std::string &bytes);
    void writePng(Image &image, std::string filename);

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};


#endif
