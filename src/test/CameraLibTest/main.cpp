#include <iostream>
#include <string>
#include <Camera/Camera.h>
#include <msleep.hpp>

int main() {
    Camera camera;
    camera.open();

    for(int i=0; i<10; i++){
        camera.capture();
        // std::string frame = camera.encode();
        // std::cout << frame << std::endl;
        camera.save("/opt/raptor/image/"+std::to_string(i)+".png");
        msleep(1000);
    }
    return 0;
}
