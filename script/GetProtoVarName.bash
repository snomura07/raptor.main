#!/bin/bash

# protoから変数名を抽出する
# 入力ファイル名
proto_file=$1

# 出力ファイル
output_file=$2

# 型と文字列を抽出するパターン
pattern='(string|int32|float)\s+([a-zA-Z0-9_]+)'

# パターンにマッチする行を抽出して型と文字列部分を取得し、出力ファイルに書き込む
grep -E -o "$pattern" "$proto_file" | awk '{print $1, $2}' > "$output_file"
