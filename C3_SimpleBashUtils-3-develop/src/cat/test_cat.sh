#!/bin/bash

# Define the flags to test
flags=(-b -e -E -n -s -t -v --number --number-nonblank --squeeze-blank)

# Define the test files
files=(testfile1.txt testfile2.txt)

# Test each flag with each file
for flag in "${flags[@]}"; do
    for file in "${files[@]}"; do
        echo "Testing flag $flag with file $file..."

        # Run s21_cat and cat with the same flag and file, and save the output
        s21_output=$(./s21_cat $flag $file)
        cat_output=$(cat $flag $file)

        # Compare the output
        if [ "$s21_output" == "$cat_output" ]; then
            echo "\033[1;32mTEST PASSED\033[m"
        else
            echo "\033[1;31mTEST FAILED\033[m"
        fi
    done
done