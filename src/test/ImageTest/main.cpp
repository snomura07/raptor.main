#include <iostream>
#include <string>
#include <Image/Image.h>
#include <datetime.hpp>

int main() {
    Image image("/opt/raptor/image/test.png");
    std::cout << image.width() << std::endl;
    image.saveAsPng("/opt/raptor/image/ggg.png");

    std::string encodedImage = image.encode();
    Image image2;
    image2.decode(encodedImage);
    image2.saveAsPng("/opt/raptor/image/fff.png");

    Image image3;
    image3.readFromFile("/opt/raptor/image/test.png");
    image3.saveAsPng("/opt/raptor/image/ddd.png");

    Image image4;
    image4.readFromBinary(encodedImage);
    image4.setTime();
    image4.saveAsPng("/opt/raptor/image/" + DateTime::getCompactDateTime() + ".png");

    return 0;
}
