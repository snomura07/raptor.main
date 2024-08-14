#include <iostream>
#include <string>
#include <print.hpp>
#include <str.hpp>
#include <ApiClient/ApiClient.h>

int main()
{
    ApiClient apiClient;

    std::string json_data = R"({"message": "これはINFOメッセージです", "type": "info"})";

    print(apiClient.post("/send", json_data));

    print(strJoin("http://","localhost",":",500));

    return 0;
}
