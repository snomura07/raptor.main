#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    // JSONファイルのパス
    std::string json_file_path = "/usr/local/config/example.json";

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
