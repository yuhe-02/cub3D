#!/bin/bash

target_dir=".."
cd $target_dir && make re

directory="./maps/cub/ng"
error_log="error.txt"
> "$error_log"

find "$directory" -type f | sort | while read file; do
    echo "-----------------------"
    echo "pattern: $file"
    echo -e "\n# Test case: $file" >> "$error_log"
    echo -e "\n# Starting test for: $file\n" >> "$error_log"
    valgrind --leak-check=full --track-fds=yes -q ./Cub3D "$file" 2>> "$error_log"
    echo -e "\n# End of test case: $file\n" >> "$error_log"
    echo "-----------------------"
done
