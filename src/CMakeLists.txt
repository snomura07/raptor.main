cmake_minimum_required(VERSION 3.0)
project(mod1)

include_directories(
)

# クロスコンパイル用のツールチェインを指定
set(CMAKE_C_COMPILER "arm-linux-gnueabi-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabi-g++")

# ソースファイルを追加
add_executable(
    hoge
    mod1.cpp
)

target_include_directories(
    hoge
    PRIVATE
    /usr/local/include
)

# 必要に応じてライブラリやリンクするものを追加
target_link_libraries(
    hoge
    PRIVATE
    pthread
    pigpio
    zmq
)

##################

# ソースファイルを追加
add_executable(
    hoge2
    mod2.cpp
)

target_include_directories(
    hoge2
    PRIVATE
    /usr/local/include
)

# 必要に応じてライブラリやリンクするものを追加
target_link_libraries(
    hoge2
    PRIVATE
    pthread
    # pigpio
    zmq
)
