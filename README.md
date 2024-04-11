# sandbox

## ピンアサイン
![ピンアサイン](https://hara-jp.com/images/_default/Topics/RaspPiZero/RaspPiZero.png)


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

## 初期設定@ラズパイ
```sudo apt update```

```sudo apt upgrade```

## pigpioインストール@ラズパイ
- 依存関係1 @ コンテナ（pythonのバージョンを合わせるため）

```sudo apt download python3-lib2to3```

```sudo apt download python3-distutils```

- 依存関係2 @ ラズパイ

```sudo dpkg -i python3-lib2to3パッケージ名```

```sudo dpkg -i python3-distutilsパッケージ名```


- packageダウンロード @ホストPC

```wget https://github.com/joan2937/pigpio/archive/master.zip```

- packageコピー @ホストPC to ラズパイ

```scp master.zip pi@192.168.137.xxx```

- 展開後make @ラズパイ

```unzip master.zip```

```make install```

## zmqインストール@ラズパイ
```sudo apt install libzmq3-dev```

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

`sudo systemctl enable raptor.service`
