## はじめに
x86用とarm用のdocker imageをビルドする

## セットアップ
ARMv6アーキテクチャ用にビルドするために、Docker Buildxを設定する
```
docker buildx create --use
docker buildx inspect --bootstrap
```

## ビルド実行
```
bash armv6/build-armv6.bash
bash x86_64/build-x86-64.bash
```

## Docker Hubにpush
```
./push_image.bash raptor_armv6_build_img
./push_image.bash raptor_x86_64_build_img
```
