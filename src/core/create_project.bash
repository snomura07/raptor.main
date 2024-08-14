#!/bin/bash

# 引数チェック
if [ $# -ne 1 ]; then
  echo "Usage: $0 <project name>"
  exit 1
fi

# 引数から新しい名前を取得
NEW_NAME=$1

# コピー元のディレクトリ名
TEMPLATE_DIR="template"

# コピー先のディレクトリ名
NEW_DIR="$NEW_NAME"

# templateディレクトリをコピー
cp -r "$TEMPLATE_DIR" "$NEW_DIR"

# コピーしたディレクトリ内のファイル名と内容を置換
find "$NEW_DIR" -type f | while read FILE; do
  # ファイル名に ****** が含まれている場合、置換してリネーム
  if [[ "$FILE" == *\*\*\*\*\*\** ]]; then
    NEW_FILE=$(echo "$FILE" | sed "s/\*\*\*\*\*\*/$NEW_NAME/g")
    mv "$FILE" "$NEW_FILE"
    FILE="$NEW_FILE"
  fi

  # ファイル内容の置換
  sed -i "s/\*\*\*\*\*\*/$NEW_NAME/g" "$FILE"
done

echo "create project $NEW_DIR"
