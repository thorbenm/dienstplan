#!/bin/bash
BASEDIR=$(dirname "$0")
cd "$BASEDIR"
rm a.out
g++ main.cpp
./a.out
