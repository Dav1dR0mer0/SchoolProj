#!/bin/bash

# Define the flags to test
flags=(-e -i -c -l -n -h -v -o)

arguments=(lol dog cat CAT)

# Define the test files
files=(testfile1.txt testfile2.txt)

# Test each flag with each file
for flag in "${flags[@]}"; do
    for file in "${files[@]}"; do
        for argument in "${arguments[@]}"; do  # Add a do statement here
            echo "$flag $argument $file..."

            # Run s21_grep and grep with the same flag and file, and save the output
            s21_output=$(./s21_grep "$flag" "$argument" "$file")
            grep_output=$(grep "$flag" "$argument" "$file")

            # Compare the output
            if [ "$s21_output" == "$grep_output" ]; then
                echo "\033[1;33m TEST PASSED \033[m"
            else
                echo "\033[1;34m TEST FAILED \033[m"
            fi
        done  # Close the for loop with a done statement
    done
done
