#!/bin/bash
BASEDIR=$(dirname "$0")
cd "$BASEDIR"
rm a.out
rm main.cpp
cat main.cpp1 >> main.cpp
cat data.txt >> main.cpp
cat main.cpp2 >> main.cpp
g++ -std=c++11 main.cpp
./a.out
