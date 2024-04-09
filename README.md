# sandbox

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
