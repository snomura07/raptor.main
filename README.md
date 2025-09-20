# sandbox

## ピンアサイン
![ピンアサイン](https://hara-jp.com/images/_default/Topics/RaspPiZero/RaspPiZero.png)


## IP固定

```
sudo nano /etc/dhcpcd.conf
```
- 以下を追記
```
interface wlan0
static ip_address=100.64.1.200/24
static routers=100.64.1.1
static domain_name_servers=100.64.1.1 8.8.8.8
```
## OTG設定
- boot直下に空の「SSH」ファイルを作成
- config.txtの末尾に、`dtoverlay=dwc2`を追記
```
~
[all]
dtoverlay=dwc2 <---追加
```
- cmdline.txtの`rootwait`の直後に半角スペースを入れて、`modules-load=dwc2,g_ether`を追記

- OTGdriverをインストール
    - https://www.catalog.update.microsoft.com/Search.aspx?q=Ethernet%2FRNDIS%20Gadget

- ssh
```
ssh pi@raspberrypi.local
```

## 初期設定@ラズパイ
```
sudo apt update
sudo apt upgrade
```

## pigpioインストール@ラズパイ
- 依存関係1 @ コンテナ（pythonのバージョンを合わせるため）
```
sudo apt download python3-lib2to3
sudo apt download python3-distutils
```

- 依存関係2 @ ラズパイ
```
sudo dpkg -i python3-lib2to3パッケージ名
sudo dpkg -i python3-distutilsパッケージ名
```


- packageダウンロード @ホストPC
```
wget https://github.com/joan2937/pigpio/archive/master.zip
```

- packageコピー @ホストPC to ラズパイ
```
scp master.zip pi@192.168.137.xxx
```

- 展開後make @ラズパイ
```
unzip master.zip
make install
```

## デーモンの登録
- サービスファイル作成@/etc/systemd/system/raptor.service

``` sss
[Unit]
Description=Raptor Service
After=network.target

[Service]
Type=simple
ExecStart=/bin/bash /home/nomura/setup.bash
WorkingDirectory=/home/nomura
Restart=always

[Install]
WantedBy=multi-user.target
```

- 有効化

```
sudo systemctl enable raptor.service
```

## シリアル通信の有効化
- raspi-configの設定
```
sudo raspi-config
 > 3 Interface Options
 > I6 Serial Port
 > yesを押下後に再起動
ls -l /dev/serial*
```
- udevに権限付与
```
nano .bashrc
 > sudo chmod 666 /dev/ttyS0
source .bashrc
```

- 不要なデーモンを上書き
```
sudo mkdir /etc/systemd/system/serial-getty@ttyS0.service.d
cd /etc/systemd/system/serial-getty@ttyS0.service.d
sudo nano override.conf

    [Service]
    ExecStart=
    ExecStart=-/sbin/agetty --keep-baud 115200,38400,9600 %I $TERM

sudo systemctl daemon-reload
sudo systemctl stop serial-getty@ttyS0.service
sudo systemctl disable serial-getty@ttyS0.service
```

## コーディングについて
- クロスコンパイルしている都合で、動的ライブラリ(.so)は設定が大変なので静的ライブラリ(.a)を使用する

## openCVのインストール
```
sudo apt update
sudo apt install libopencv-dev
```

## zmqインストール@ラズパイ
```
sudo apt install libzmq3-dev
```

## protobufインストール@ラズパイ
```
git clone --branch v3.5.1 https://github.com/protocolbuffers/protobuf.git
cd protobuf
git submodule update --init --recursive
./autogen.sh
./configure
make
make install
```

## 実行方法@コンテナ内
```
qemu-arm -L /usr/arm-linux-gnueabi /opt/raptor/bin/Zserver
or
exec /opt/raptor/bin/Zserver ※alias登録済み
```
