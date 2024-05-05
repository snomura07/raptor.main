#include <pigpio.h>
#include <iostream>
#include <unistd.h>

int main() {
    // pigpioライブラリを初期化する
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed" << std::endl;
        return 1;
    }

    // GPIO 17ピンを出力モードに設定する
    gpioSetMode(17, PI_OUTPUT);

    // GPIO 17ピンをOFFにする
    gpioWrite(17, 0);

    // 1秒待つ
    usleep(1000000);

    // pigpioライブラリを解放する
    gpioTerminate();

    return 0;
}
