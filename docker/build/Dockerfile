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
    qemu-user-binfmt

    # install pigio for GPIO
WORKDIR /package
RUN wget https://github.com/joan2937/pigpio/archive/master.zip
RUN unzip master.zip
WORKDIR  /package/pigpio-master
RUN sed -i 's/^CROSS_PREFIX =.*/CROSS_PREFIX =arm-linux-gnueabi-/' Makefile
RUN make install

# ライブラリビルド＆インストール
# クロスコンパイル用の環境変数設定
ENV CC=arm-linux-gnueabi-gcc \
    CXX=arm-linux-gnueabi-g++ \
    AR=arm-linux-gnueabi-ar \
    RANLIB=arm-linux-gnueabi-ranlib \
    LD=arm-linux-gnueabi-ld \
    AS=arm-linux-gnueabi-as

# ZMQ
RUN git clone https://github.com/zeromq/libzmq.git /tmp/libzmq
RUN cd /tmp/libzmq && \
    ./autogen.sh && \
    ./configure --host=arm-linux-gnueabi && \
    make && \
    make install

# protobuf
RUN git clone --branch v3.7.1 https://github.com/protocolbuffers/protobuf.git /tmp/protobuf
RUN cd /tmp/protobuf && \
    git submodule update --init --recursive && \
    ./autogen.sh && \
    ./configure --host=arm-linux-gnueabi --prefix=/usr/arm-linux-gnueabi && \
    make && \
    make install

# opencv
# 静的ライブラリとしてビルド
RUN wget https://github.com/opencv/opencv/archive/4.2.0.zip -O /tmp/opencv.zip && \
    unzip /tmp/opencv.zip -d /tmp && \
    mv /tmp/opencv-4.2.0 /tmp/opencv && \
    cd /tmp/opencv && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release \
          -D CMAKE_TOOLCHAIN_FILE=../platforms/linux/arm-gnueabi.toolchain.cmake \
          -D CMAKE_INSTALL_PREFIX=/usr/local \
          -DBUILD_SHARED_LIBS=OFF \
          .. && \
    make -j$(nproc) && \
    make install

# ライブラリパスの設定
RUN ldconfig

# add sudo user
RUN groupadd -g 1000 developer && \
    useradd  -g      developer -G sudo -m -s /bin/bash nomura && \
    echo 'nomura:robo2006' | chpasswd
RUN echo 'Defaults visiblepw'             >> /etc/sudoers
RUN echo 'nomura ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER nomura
WORKDIR /home/nomura

# Add LD_LIBRARY_PATH to point to the cross-compiled libraries
ENV LD_LIBRARY_PATH=/usr/local/lib
ENV LD_LIBRARY_PATH=/home/nomura/lib:$LD_LIBRARY_PATH
RUN echo 'exec(){ qemu-arm -L /usr/arm-linux-gnueabi $@; }' >> .bashrc
