#include <pigpio.h>
#include <iostream>
#include <unistd.h>

int main() {
    // pigpioライブラリを初期化する
    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialization failed" << std::endl;
        return 1;
    }

    // GPIO 14ピンを出力モードに設定する
    gpioSetMode(14, PI_OUTPUT);

    // GPIO 14ピンをOFFにする
    gpioWrite(14, 0);

    // 1秒待つ
    usleep(1000000);

    // pigpioライブラリを解放する
    gpioTerminate();

    return 0;
}
