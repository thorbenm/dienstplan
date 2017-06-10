#!/bin/bash
BASEDIR=$(dirname "$0")
cd "$BASEDIR"
rm a.out
g++ -std=c++11 main.cpp
./a.out
