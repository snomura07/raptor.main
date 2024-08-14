#include <iostream>
#include <print.hpp>
#include <httplib.h>

int main()
{
    httplib::Client cli("http://chat:5000");

    // JSONデータを直接文字列として作成
    std::string json_data = R"({"message": "これはINFOメッセージです", "type": "info"})";

    // POSTリクエストを送信
    auto res = cli.Post("/send", json_data, "application/json");

    // レスポンスを確認
    if (res && res->status == 200) {
        std::cout << "Response: " << res->body << std::endl;
    } else {
        std::cerr << "Request failed with status code: " << res->status << std::endl;
    }

    return 0;
}
