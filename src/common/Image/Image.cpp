#include "Image.h"
#include <iostream>
#include <cstring>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <opencv2/opencv.hpp>

class Image::Impl{
public:
    Impl()
        : width(0), height(0), channel(0), size(0) {
    }
    Impl(const std::string& imgFilePath)
        : width(0), height(0), channel(0), size(0) {
        readFromFile(imgFilePath);
    }

    void readFromMat(const cv::Mat &mat)
    {
        frame = mat;
        if (!frame.empty()) {
            width   = frame.cols;
            height  = frame.rows;
            channel = frame.channels();
            size    = width * height * channel;
        } else {
            std::cerr << "Failed to load image from mat"<< std::endl;
        }
    }

    void readFromFile(const std::string &imgFilePath)
    {
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

    void readFromBinary(const std::string &bin)
    {
        std::vector<uchar> buf(bin.begin(), bin.end());
        cv::Mat decodedImage = cv::imdecode(buf, cv::IMREAD_ANYCOLOR);
        if (!decodedImage.empty()) {
            frame   = decodedImage;
            width   = frame.cols;
            height  = frame.rows;
            channel = frame.channels();
            size    = width * height * channel;
        } else {
            std::cerr << "Failed to decode image from binary." << std::endl;
        }
    }

    int width;
    int height;
    int channel;
    int size;
    cv::Mat frame;
};

Image::Image()
    : pImpl(std::make_unique<Impl>()) {}
Image::Image(const std::string& imgFilePath)
    : pImpl(std::make_unique<Impl>(imgFilePath)) {}
Image::~Image() = default;
int Image::width()                 { return pImpl->width; }
int Image::height()                { return pImpl->height; }
int Image::channel()               { return pImpl->channel; }
int Image::size()                  { return pImpl->size; }
const unsigned char* Image::data() { return pImpl->frame.data; }

void Image::readFromMat(const cv::Mat &mat)
{
    pImpl->readFromMat(mat);
}

void Image::readFromFile(const std::string &imgFilePath)
{
    pImpl->readFromFile(imgFilePath);
}

void Image:: readFromBinary(const std::string &bin)
{
    pImpl->readFromBinary(bin);
}

void Image::saveAsPng(const std::string &filename) {
    if (!pImpl->frame.empty()) {
        if (cv::imwrite(filename, pImpl->frame)) {
            std::cout << "Image saved as " << filename << std::endl;
        } else {
            std::cerr << "Failed to save image to " << filename << std::endl;
        }
    } else {
        std::cerr << "No image to save." << std::endl;
    }
}

std::string Image::encode()
{
    std::vector<uchar> buf;
    bool success = cv::imencode(".png", pImpl->frame, buf);
    if (!success) {
        std::cerr << "Failed to encode image." << std::endl;
        return "";
    }
    return std::string(buf.begin(), buf.end());
}

void Image::decode(const std::string &bin)
{
    std::vector<uchar> buf(bin.begin(), bin.end());
    if (buf.empty()) {
        std::cerr << "Received empty binary data." << std::endl;
        return;
    }
    cv::Mat decodedImage = cv::imdecode(buf, cv::IMREAD_ANYCOLOR);
    if (!decodedImage.empty()) {
        pImpl->frame   = decodedImage;
        pImpl->width   = pImpl->frame.cols;
        pImpl->height  = pImpl->frame.rows;
        pImpl->channel = pImpl->frame.channels();
        pImpl->size    = pImpl->width * pImpl->height * pImpl->channel;
    } else {
        std::cerr << "Failed to decode image from binary." << std::endl;
    }
}

void Image::setTime()
{
    // 現在の日時を取得
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // ローカルタイムに変換
    struct tm buf;
    localtime_r(&in_time_t, &buf);

    // 日時を文字列形式でフォーマット
    std::ostringstream ss;
    ss << std::put_time(&buf, "%Y/%m/%d %H:%M:%S");

    std::string timeText = ss.str();
    cv::Point textOrg(10, 30);  // テキストの位置
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 0.7;
    int thickness = 1;
    cv::Scalar textColor(255, 255, 255); // テキストの色（白）
    cv::Scalar backgroundColor(0, 0, 0); // 背景色（黒）

    // テキストのサイズとベースラインを取得
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(timeText, fontFace, fontScale, thickness, &baseline);

    // 背景の黒長方形を描画
    cv::rectangle(pImpl->frame, textOrg + cv::Point(0, baseline), textOrg + cv::Point(textSize.width, -textSize.height), backgroundColor, cv::FILLED);

    // テキストを描画
    cv::putText(pImpl->frame, timeText, textOrg, fontFace, fontScale, textColor, thickness);
}
