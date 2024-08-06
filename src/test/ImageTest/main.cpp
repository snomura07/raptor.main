#include <iostream>
#include <string>
#include <Image/Image.h>

int main() {
    Image image("/home/nomura/image/test.png");
    std::cout << image.width() << std::endl;
    image.saveAsPng("/home/nomura/image/ggg.png");

    std::string encodedImage = image.encode();
    Image image2;
    image2.decode(encodedImage);
    image2.saveAsPng("/home/nomura/image/fff.png");
    
    Image image3;
    image3.readFromFile("/home/nomura/image/test.png");
    image3.saveAsPng("/home/nomura/image/ddd.png");

    Image image4;
    image4.readFromBinary(encodedImage);
    image4.setTime();
    image4.saveAsPng("/home/nomura/image/hhh.png");

    return 0;
}
