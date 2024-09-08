#include <iostream>
#include <string>
#include <print.hpp>
#include <msleep.hpp>
// #include <zmq.h>
#include <ZmqWrapper/ZmqWrapper.h>
#include <cstring>

int main(int argc, char **argv)
{
    ZmqWrapper zmq;
    zmq.registerSession("chat", 5001 , ZmqWrapper::zmqPatternEnum::PUBLISH, "ZIMAGE");

    while(1){
        zmq.sendMessage("send message!");
        print("send!");
        msleep(1000);
    }

    // // ZeroMQのコンテキストとソケットの初期化
    // void* context = zmq_ctx_new();
    // void* socket = zmq_socket(context, ZMQ_PUB);

    // // サーバーのアドレスに接続
    // zmq_connect(socket, "tcp://chat:5001");

    // const char* topic = "ZIMAGE";

    // while (true) {
    //     const char* message = "Hello from C++!";
    //     char full_message[256];
    //     snprintf(full_message, sizeof(full_message), "%s %s", topic, message);

    //     // メッセージを送信
    //     zmq_send(socket, full_message, strlen(full_message), 0);

    //     std::cout << "Sent message: " << full_message << std::endl;

    //     // 少し待機
    //     msleep(1000);
    // }

    // // ソケットとコンテキストのクリーンアップ
    // zmq_close(socket);
    // zmq_ctx_destroy(context);
}
