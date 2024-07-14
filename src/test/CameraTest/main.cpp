#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Failed to open the camera on index 0" << std::endl;
        return -1;
    } else {
        std::cout << "Camera successfully opened on index 0" << std::endl;
    }

    // カメラ設定の例: フレームサイズ 640x480, フォーマット YUYV
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('Y', 'U', 'Y', 'V'));

    std::cout << "Frame width: " << cap.get(cv::CAP_PROP_FRAME_WIDTH) << std::endl;
    std::cout << "Frame height: " << cap.get(cv::CAP_PROP_FRAME_HEIGHT) << std::endl;
    std::cout << "FourCC: " << cap.get(cv::CAP_PROP_FOURCC) << std::endl;

    cv::Mat frame;
    cap >> frame;

    if (frame.empty()) {
        std::cerr << "Failed to capture frame" << std::endl;
        return -1;
    } else {
        std::cout << "Frame captured successfully" << std::endl;
    }

    std::string filename = "./test.png";
    if (!cv::imwrite(filename, frame)) {
        std::cerr << "Failed to save image to " << filename << std::endl;
    } else {
        std::cout << "Image saved as " << filename << std::endl;
    }

    return 0;
}
