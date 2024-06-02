#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Open the camera
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cout << "Failed to open the camera" << std::endl;
        return -1;
    }

    // Capture a frame
    std::queue<cv::Mat> frameQueue;
    while (true) {
        // Capture a frame
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            std::cout << "Failed to capture frame" << std::endl;
            return -1;
        }

        // Add the frame to the queue
        frameQueue.push(frame);

        // Check if the queue size exceeds the maximum limit
        if (frameQueue.size() > 10) {
            // Remove the oldest frame from the queue
            frameQueue.pop();
        }

        // Save the frame as a PNG file
        std::string filename = "./test.png";
        cv::imwrite(filename, frame);
        std::cout << "Image saved as " << filename << std::endl;

        // Delay for 1 second
        cv::waitKey(1000);
    }

    // Release the camera capture
    cap.release();

    return 0;
}
