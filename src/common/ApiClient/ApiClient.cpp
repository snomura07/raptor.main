#include <print.hpp>
#include <str.hpp>
#include "ApiClient.h"

ApiClient::ApiClient()
{
    masterConf.read();
}

ApiClient::~ApiClient(){}

std::string ApiClient::post(std::string path, std::string msg)
{
    httplib::Client cli(strJoin("http://",masterConf.apiHost,":",masterConf.apiPort));
    cli.set_connection_timeout(1, 0); // 1秒 (秒, マイクロ秒)
    cli.set_read_timeout(1, 0);
    cli.set_write_timeout(1, 0);

    auto res = cli.Post(path, msg, "application/json");

    if (res && res->status == 200) {
        return res->body;
    } else {
        return "Request failed";
    }
}

std::string ApiClient::post(std::string endpoint, std::string path, std::string msg)
{
    httplib::SSLClient cli(endpoint.c_str());
    // CA証明書のパスを明示
    cli.set_ca_cert_path("/etc/ssl/certs/ca-certificates.crt");
    cli.enable_server_certificate_verification(true);

    cli.set_connection_timeout(5, 0);
    cli.set_read_timeout(5, 0);

    httplib::Headers headers = {
        { "Content-Type", "application/json" }
    };

    auto res = cli.Post(path.c_str(), headers, msg, "application/json");

    // レスポンス処理
    if (res && res->status == 200) {
        return res->body;
    } else if (res) {
        return "Error: HTTP " + std::to_string(res->status);
    } else {
        return "Error: Connection failed";
    }
}

std::string ApiClient::get(std::string path, std::string msg)
{
    return "";
}
