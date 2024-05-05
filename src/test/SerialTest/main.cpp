#include <pigpio.h>
#include <iostream>
#include <unistd.h>

#define UART_DEVICE "/dev/serial0"
#define BAUD_RATE 38400
#define FRAME_SIZE 6

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
        char bytes[FRAME_SIZE];
        int bytes_read = serRead(uart_handle, bytes, FRAME_SIZE);
        if (bytes_read > 1) {
            std::cout << "Received data: ";
            for (int i = 0; i < FRAME_SIZE; ++i) {
                std::cout << std::hex << static_cast<int>(bytes[i]) << " ";
            }
            std::cout << std::endl;
        }
        usleep(10000);
    }

    serClose(uart_handle);
    gpioTerminate();
    return 0;
}
