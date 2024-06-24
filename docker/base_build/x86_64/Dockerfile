# GLIBC 2.31のために固定
FROM ubuntu:20.04

# for timezone
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y --fix-missing \
    cmake \
    git \
    wget \
    nano \
    python3-pip \
    curl \
    sudo \
    unzip \
    g++-arm-linux-gnueabi \
    libtool \
    autoconf \
    automake \
    pkg-config \
    qemu-user-binfmt \
    libgtk2.0-dev

# ホスト用Protobuf v3.5.1のインストール
WORKDIR /tmp
RUN wget https://github.com/protocolbuffers/protobuf/archive/v3.5.1.tar.gz && \
    tar -xzf v3.5.1.tar.gz && \
    cd protobuf-3.5.1 && \
    ./autogen.sh && \
    ./configure && \
    make -j$(nproc) && \
    sudo make install && \
    sudo ldconfig

# ライブラリビルド＆インストール
# クロスコンパイル用の環境変数設定
ENV CC=arm-linux-gnueabi-gcc \
    CXX=arm-linux-gnueabi-g++ \
    AR=arm-linux-gnueabi-ar \
    RANLIB=arm-linux-gnueabi-ranlib \
    LD=arm-linux-gnueabi-ld \
    AS=arm-linux-gnueabi-as

# protobuf
# libtoolの設定を変更して、カスタムインストール先ディレクトリを使用
RUN cd /tmp/protobuf-3.5.1 && \
    make clean && \
    ./configure --host=arm-linux-gnueabi --prefix=/usr/arm-linux-gnueabi --with-protoc=/usr/local/bin/protoc ac_cv_c_compiler_working=yes && \
    sed -i 's|^libdir=.*|libdir="/usr/arm-linux-gnueabi/lib"|' libtool && \
    ./autogen.sh && \
    ./configure --host=arm-linux-gnueabi --prefix=/usr/arm-linux-gnueabi --with-protoc=/usr/local/bin/protoc ac_cv_c_compiler_working=yes && \
    make -j$(nproc) && \
    sudo make install && \
    sudo ldconfig

# install pigio for GPIO
WORKDIR /tmp
RUN wget https://github.com/joan2937/pigpio/archive/master.zip
RUN unzip master.zip
WORKDIR  /tmp/pigpio-master
RUN sed -i 's/^CROSS_PREFIX =.*/CROSS_PREFIX =arm-linux-gnueabi-/' Makefile
RUN make install PREFIX=/usr/arm-linux-gnueabi

# ZMQ
RUN git clone https://github.com/zeromq/libzmq.git /tmp/libzmq
RUN cd /tmp/libzmq && \
    ./autogen.sh && \
    ./configure --host=arm-linux-gnueabi --prefix=/usr/arm-linux-gnueabi && \
    make -j$(nproc) && \
    make install

# opencv
# 静的ライブラリとしてビルド
RUN wget https://github.com/opencv/opencv/archive/4.7.0.zip -O /tmp/opencv.zip && \
    unzip /tmp/opencv.zip -d /tmp && \
    mv /tmp/opencv-4.7.0 /tmp/opencv && \
    cd /tmp/opencv && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release \
          -D CMAKE_TOOLCHAIN_FILE=../platforms/linux/arm-gnueabi.toolchain.cmake \
          -D CMAKE_INSTALL_PREFIX=/usr/arm-linux-gnueabi \
          -D OpenCV_DIR=/usr/arm-linux-gnueabi/lib/cmake/opencv4 \
          .. && \
    make -j$(nproc) && \
    make install

    # ライブラリパスの設定
RUN ldconfig
