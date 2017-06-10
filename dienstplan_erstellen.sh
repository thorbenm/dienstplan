#!/bin/bash
BASEDIR=$(dirname "$0")
cd "$BASEDIR"
cat sourcecode/main.cpp1 >> main.cpp
cat freiwuensche.txt >> main.cpp
cat sourcecode/main.cpp2 >> main.cpp
g++ -std=c++11 main.cpp
./a.out
rm a.out
rm main.cpp
