#include <iostream>
#include <Camera/Camera.h>

int main() {
    Camera camera;
    camera.open();
    camera.capture();
    camera.save("/home/nomura/image/ggg.png");
    return 0;
}
