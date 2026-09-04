#!/bin/bash
for ((i=1; ; i++)); do
    ./gen > input.txt           # generator
    ./code < input.txt > output1.txt  # your code
    ./std < input.txt > output2.txt   # std code
    if diff output1.txt output2.txt; then  # compare
        echo "Test $i: Accepted"
    else
        echo "Test $i: Wrong Answer"
        echo "Input:"
        cat input.txt
        echo "Your Output:"
        cat output1.txt
        echo "Standard Output:"
        cat output2.txt
        break
    fi
done