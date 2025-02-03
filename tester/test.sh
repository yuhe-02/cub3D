#!/bin/bash

target_dir="../project"
cd $target_dir
make re

directory="./maps/cubfiles/ng"
programe_name="./cub3D"
error_log="../tester/error.txt"
> "$error_log"

find "$directory" -type f | sort | while read file; do
    echo "-----------------------"
    echo "pattern: $file"
    echo -e "-----------------------" >> "$error_log"
    echo -e "# Test case: $file" >> "$error_log"
    echo -e "# Starting test for: $file\n" >> "$error_log"
    # valgrind --leak-check=full --track-fds=yes -q "$programe_name" "$file" 2>> "$error_log"
    valgrind --leak-check=full -q "$programe_name" "$file" 2>> "$error_log"
    echo -e "-----------------------" >> "$error_log"
    # echo -e "\n# End of test case: $file\n" >> "$error_log"
    echo "-----------------------"
done
