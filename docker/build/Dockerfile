# GLIBC 2.31のために固定
FROM ubuntu:20.04

# for timezone
ENV DEBIAN_FRONTEND=noninteractive

RUN apt update
RUN apt install -y  \
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

# ZMQインストール
# クロスコンパイル用の環境変数設定
ENV CC=arm-linux-gnueabi-gcc \
    CXX=arm-linux-gnueabi-g++ \
    AR=arm-linux-gnueabi-ar \
    RANLIB=arm-linux-gnueabi-ranlib \
    LD=arm-linux-gnueabi-ld \
    AS=arm-linux-gnueabi-as

# ZMQのソースコードをダウンロード
RUN git clone https://github.com/zeromq/libzmq.git /tmp/libzmq

# コンパイルとインストール
RUN cd /tmp/libzmq && \
    ./autogen.sh && \
    ./configure --host=arm-linux-gnueabi && \
    make && \
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
RUN echo 'exec(){ qemu-arm -L /usr/arm-linux-gnueabi $@; }' >> .bashrc