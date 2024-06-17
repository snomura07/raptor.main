cmake_minimum_required(VERSION 3.0)
project(Raptor)

# クロスコンパイル用のツールチェインを指定
set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Opencv
set(OpenCV_DIR /usr/arm-linux-gnueabi/lib/cmake/opencv4)

# include dirs
set(INCLUDE_DIRS /usr/local/include/)

# install prefix
set(CMAKE_INSTALL_PREFIX ../)

# script path
set(SCRIPT_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/../script/)

add_subdirectory(core)
add_subdirectory(common)
add_subdirectory(protobuf)
add_subdirectory(test)
