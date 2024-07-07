FROM balenalib/rpi-raspbian:bullseye

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
    libtool \
    autoconf \
    automake \
    pkg-config \
    libgtk2.0-dev \
    build-essential \
    libatlas-base-dev \
    gfortran \
    python3-dev \
    libtbb2 \
    libtbb-dev \
    libdc1394-22-dev \
    libjpeg-dev \
    libpng-dev \
    libtiff-dev \
    libavcodec-dev \
    libavformat-dev \
    libswscale-dev \
    libv4l-dev \
    libxvidcore-dev \
    libx264-dev \
    libgtk2.0-dev \
    && rm -rf /var/lib/apt/lists/*


# ホスト用Protobuf v3.5.1のインストール
WORKDIR /tmp
RUN wget https://github.com/protocolbuffers/protobuf/archive/v3.5.1.tar.gz && \
    tar -xzf v3.5.1.tar.gz && \
    cd protobuf-3.5.1 && \
    ./autogen.sh && \
    ./configure && \
    make -j$(nproc) && \
    make -j$(nproc) install && \
    ldconfig

# install pigio for GPIO
WORKDIR /tmp
RUN wget https://github.com/joan2937/pigpio/archive/master.zip
RUN unzip master.zip
WORKDIR  /tmp/pigpio-master
RUN make -j$(nproc) install

# ZMQ
RUN git clone https://github.com/zeromq/libzmq.git /tmp/libzmq
RUN cd /tmp/libzmq && \
    ./autogen.sh && \
    ./configure && \
    make -j$(nproc) && \
    make -j$(nproc) install

# opencv
# 静的ライブラリとしてビルド
RUN wget https://github.com/opencv/opencv/archive/4.7.0.zip -O /tmp/opencv.zip && \
    unzip /tmp/opencv.zip -d /tmp && \
    mv /tmp/opencv-4.7.0 /tmp/opencv && \
    cd /tmp/opencv && \
    mkdir build && \
    cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release \
          -D CMAKE_INSTALL_PREFIX=/usr/local \
          -D BUILD_TESTS=OFF \
          -D BUILD_EXAMPLES=OFF \
          -D WITH_V4L=ON \
          -D WITH_LIBV4L=ON \
          -DCMAKE_CXX_FLAGS="-latomic" \
          -DCMAKE_SHARED_LINKER_FLAGS="-latomic" \
          .. && \
    make -j$(nproc) VERBOSE=1 && \
    make -j$(nproc) install && \
    rm -rf /tmp/opencv* && \
    ldconfig

    # ライブラリパスの設定
RUN ldconfig
RUN ln -s /usr/lib/arm-linux-gnueabihf/ld-linux.so.3 /lib/ld-linux.so.3
