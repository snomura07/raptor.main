cmake_minimum_required(VERSION 3.0)
project(Raptor)

# クロスコンパイル用のツールチェインを指定
set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabi-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# lib dirs
set(LIB_DIRS /usr/local/include/)

# install
set(CMAKE_INSTALL_PREFIX ../)

# add_subdirectory(proc)
# add_subdirectory(utils)
add_subdirectory(test)
