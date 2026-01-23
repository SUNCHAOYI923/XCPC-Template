#!/bin/bash
ulimit -s 102400
g++ -std=c++17 -O2 -Wall "$1" -o main
./main < in.txt > out.txt