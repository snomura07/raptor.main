#include <iostream>
#include <string>
#include <Image/Image.h>

int main() {
    Image image("/usr/local/image/test.png");
    std::cout << image.width() << std::endl;
    image.saveAsPng("/usr/local/image/ggg.png");

    std::string encodedImage = image.encode();
    Image image2;
    image2.decode(encodedImage);
    image2.saveAsPng("/usr/local/image/fff.png");
    
    Image image3;
    image3.readFromFile("/usr/local/image/test.png");
    image3.saveAsPng("/usr/local/image/ddd.png");

    Image image4;
    image4.readFromBinary(encodedImage);
    image4.setTime();
    image4.saveAsPng("/usr/local/image/hhh.png");

    return 0;
}
