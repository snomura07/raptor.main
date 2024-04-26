#include <iostream>
#include <map>
#include <functional>

class Test {
public:
    // コールバック関数の型を定義
    using CallbackFunction = std::function<void(int)>;

    // コールバック関数を登録するメソッド
    void registerCallback(const std::string& name, const CallbackFunction& callback) {
        callbackMap[name] = callback;
    }

    // 登録した関数を実行するメソッド
    void run(const std::string& name, int arg) {
        if (auto it = callbackMap.find(name); it != callbackMap.end()) {
            it->second(arg); // 登録した関数を実行
        } else {
            std::cout << "Callback function not found for name: " << name << std::endl;
        }
    }

private:
    std::map<std::string, CallbackFunction> callbackMap;
};

// サンプルの関数
void function1(int x) {
    std::cout << "Function 1 called with argument: " << x << std::endl;
}

void function2(int x) {
    std::cout << "Function 2 called with argument: " << x << std::endl;
}

int main() {
    Test test;

    // 関数を登録
    test.registerCallback("func1", &function1);
    test.registerCallback("func2", &function2);

    // 登録した関数を実行
    test.run("func1", 10); // 引数を渡して実行
    test.run("func2", 20); // 引数を渡して実行
    test.run("func3", 30); // 存在しないコールバック関数の呼び出し

    return 0;
}
