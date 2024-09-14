#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    // JSON形式の文字列
    std::string json_string = R"({"main_command":"gpio/setio/high","optional_value":[16,17,18]})";
    json j2 = json::parse(json_string);
    std::cout << "JSONデータ: " << j2.dump() << std::endl;
    std::string main_command = j2["main_command"];
    std::vector<int> optional_value = j2["optional_value"].get<std::vector<int>>();
    std::cout << "メインコマンド: " << main_command << std::endl;
    std::cout << "オプション値: ";
    for (int val : optional_value) {
        std::cout << val << " ";
    }
    std::cout << std::endl;



    // JSONファイルのパス
    std::string json_file_path = "/opt/raptor/config/example.json";

    // JSONファイルを開く
    std::ifstream json_file(json_file_path);

    // ファイルが正常に開けたかチェック
    if (!json_file.is_open()) {
        std::cerr << "JSONファイルを開けませんでした。" << std::endl;
        return 1;
    }

    // JSONファイルからデータを読み込み
    json j;
    json_file >> j;

    // JSONデータの表示
    std::cout << "JSONデータ: " << j.dump() << std::endl;

    // JSONデータの操作
    std::string name = j["name"];
    int age = j["age"];

    std::cout << "名前: " << name << std::endl;
    std::cout << "年齢: " << age << std::endl;

    return 0;
}
