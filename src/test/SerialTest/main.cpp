#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <cstring>
#include <csignal>

volatile sig_atomic_t g_running = true;

void sigint_handler(int signum) {
    g_running = false;
}

int main() {
    // シグナルハンドラを設定
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    int uart_handle = open("/dev/serial0", O_RDWR | O_NOCTTY);
    if (uart_handle == -1) {
        std::cerr << "UART device open failed" << std::endl;
        return 1;
    }

    struct termios options;
    tcgetattr(uart_handle, &options);
    options.c_cflag = B38400 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart_handle, TCIFLUSH);
    tcsetattr(uart_handle, TCSANOW, &options);

    unsigned char buffer[6];

    while (g_running) {
        int bytes_read = read(uart_handle, buffer, 6);
        if (bytes_read == 6) {
            if(buffer[0] == 0xAA){
                std::cout << "Received data: ";
                for (int i = 0; i < 6; ++i) {
                    std::cout << std::hex << static_cast<int>(buffer[i]) << " ";
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "Received data: ";
                for (int i = 0; i < 6; ++i) {
                    std::cout << std::hex << static_cast<int>(buffer[i]) << " ";
                }
                std::cout << std::endl;
                tcflush(uart_handle, TCIFLUSH);
            }
        }

        usleep(10000);
    }

    // Ctrl+Cが押されたので、リソースをクリーンアップ
    close(uart_handle);
    std::cout << "Program terminated by user." << std::endl;

    return 0;
}
