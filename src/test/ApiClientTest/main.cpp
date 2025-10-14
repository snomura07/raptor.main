#include <iostream>
#include <string>
#include <print.hpp>
#include <str.hpp>
#include <ApiClient/ApiClient.h>

int main()
{
    ApiClient apiClient;

    std::string json_data = R"({"process_name":"ApiClientTest", "status":"Stopped"})";

    print(apiClient.post("prpjme5ltk.execute-api.ap-northeast-1.amazonaws.com", "/dev/set_log", json_data));

    return 0;
}
