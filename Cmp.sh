#!/bin/bash
for ((i=1; ; i++)); do
    ./gen > input.txt           # 生成数据
    ./code < input.txt > output1.txt  # 你的代码运行
    ./std < input.txt > output2.txt   # 标准答案运行
    if diff output1.txt output2.txt; then  # 比较输出
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