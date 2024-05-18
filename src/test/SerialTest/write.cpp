#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>

int main() {
    const char* portname = "/dev/serial0";
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        std::cerr << "Error opening " << portname << std::endl;
        return 1;
    }

    struct termios tty;
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(fd, &tty) != 0) {
        std::cerr << "Error from tcgetattr" << std::endl;
        return 1;
    }

    // シリアルポートの設定
    tty.c_cflag &= ~PARENB; // パリティ無し
    tty.c_cflag &= ~CSTOPB; // ストップビット1
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8; // データビット8
    tty.c_cflag &= ~CRTSCTS; // ハードウェアフロー制御なし
    tty.c_cflag |= CREAD | CLOCAL; // 受信有効、ローカルライン（モデム制御なし）

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // ローカルモードを無効にする

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // ソフトウェアフロー制御なし

    tty.c_oflag &= ~OPOST; // 出力処理なし

    tty.c_cc[VMIN] = 0; // 最小の文字数
    tty.c_cc[VTIME] = 5; // タイムアウト

    cfsetospeed(&tty, B115200); // ボーレート115200bps
    cfsetispeed(&tty, B115200);

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "Error from tcsetattr" << std::endl;
        return 1;
    }

    // 送信するデータ
    uint8_t  data_to_send[10] = {0xBB, 1, 2, 3, 4, 5, 6, 7, 8, 0x66};
    uint32_t timerCnt = 0;
    // データを送信
    while(1){
        data_to_send[1] = (timerCnt >> 24) & 0xFF;
        data_to_send[2] = (timerCnt >> 16) & 0xFF;
        data_to_send[3] = (timerCnt >> 8 ) & 0xFF;
        data_to_send[4] = (timerCnt >> 0 ) & 0xFF;


        ssize_t bytes_written = write(fd, data_to_send, 10);
        if (bytes_written != 10) {
            std::cerr << "Error writing to " << portname << std::endl;
        }

        timerCnt++;
        usleep(1000);
    }

    close(fd);
    return 0;
}
