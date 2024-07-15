#include <iostream>
#include <string>
#include <Camera/Camera.h>
#include <msleep.hpp>

int main() {
    Camera camera;
    camera.open();

    while(1){
        camera.capture();
        std::string frame = camera.encode();
        std::cout << frame << std::endl;
        msleep(1000);
    }
    // camera.save("/home/nomura/image/ggg.png");
    return 0;
}
