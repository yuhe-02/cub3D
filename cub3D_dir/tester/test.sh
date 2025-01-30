#!/bin/bash
target_dir=".."

cd $target_dir && make re

directory="./maps/cub"

find "$directory" -type f | sort | while read file; do
    # 各ファイルに対して ./cub3D コマンドを実行
    echo "-----------------------"
	echo "pattern: $file"
    ./cub3D "$file"
	echo "-----------------------"
done