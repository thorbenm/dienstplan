#!/bin/bash
BASEDIR=$(dirname "$0")
cd "$BASEDIR"
rm main.cpp
nano .sourcecode/info.txt
cat .sourcecode/main1.cpp >> main.cpp
cat .sourcecode/info.txt >> main.cpp
cat .sourcecode/main2.cpp >> main.cpp
g++ -std=c++11 main.cpp
./a.out
rm a.out
rm main.cpp
