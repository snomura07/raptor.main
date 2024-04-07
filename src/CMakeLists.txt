cmake_minimum_required(VERSION 3.0)
project(mod1)

# クロスコンパイル用のツールチェインを指定
set(CMAKE_C_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabi-g++")

# その他の設定
# ...

# ソースファイルを追加
add_executable(hoge mod1.cpp)

# 必要に応じてライブラリやリンクするものを追加
# target_link_libraries(my_executable some_library)
