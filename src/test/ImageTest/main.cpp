#include <iostream>
#include <Image/Image.h>

int main() {
    Image image("/home/nomura/image/test.png");

    std::cout << image.width() << std::endl;

    return 0;
}
