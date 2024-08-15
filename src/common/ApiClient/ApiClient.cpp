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

std::string ApiClient::get(std::string path, std::string msg)
{
    return "";
}
