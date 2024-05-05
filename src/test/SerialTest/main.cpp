#include <pigpio.h>
#include <iostream>
#include <unistd.h>

#define UART_DEVICE "/dev/serial0"
#define BAUD_RATE 38400
#define FRAME_SIZE 20

int main() {
    if (gpioInitialise() < 0) {
        std::cerr << "GPIO initialization failed" << std::endl;
        return 1;
    }

    int uart_handle = serOpen(UART_DEVICE, BAUD_RATE, 0);
    if (uart_handle < 0) {
        std::cerr << "UART device open failed" << std::endl;
        return 1;
    }

    while (true) {
        char start_byte;
        int bytes_read = serRead(uart_handle, &start_byte, 1); // スタートビットを読み込む
        if (bytes_read == 1) {
            // スタートビットが検出された場合
            char frame_data[FRAME_SIZE];
            frame_data[0] = start_byte;

            // 残りのデータを読み取る
            bytes_read = serRead(uart_handle, frame_data + 1, FRAME_SIZE - 1);

            std::cout << "Received data: ";
            for (int i = 0; i < FRAME_SIZE; ++i) {
                std::cout << std::hex << static_cast<int>(frame_data[i]) << " ";
            }
            std::cout << std::endl;

        }
    }

    serClose(uart_handle);
    gpioTerminate();
    return 0;
}
