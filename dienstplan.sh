#!/bin/bash
BASEDIR=$(dirname "$0")
cd "$BASEDIR"
rm main.cpp > /dev/null 2>&1
rm a.out > /dev/null 2>&1
nano .sourcecode/info.txt
cat .sourcecode/main1.cpp >> main.cpp
cat .sourcecode/info.txt >> main.cpp
cat .sourcecode/main2.cpp >> main.cpp
g++ -std=c++11 main.cpp
./a.out
rm a.out > /dev/null 2>&1
rm main.cpp > /dev/null 2>&1
