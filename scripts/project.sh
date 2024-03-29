#!/bin/sh

if [ "$1" = "--clean" ]; then
    rm -rf build/
    rm prusa-console
fi

if [ "$1" = "--test" ]; then
    git submodule update --init --recursive
    mkdir -p build && cd build
    cmake .. && cmake --build . && ./tests_runner
fi

if [ "$1" = "--build" ]; then
    git submodule update --init --recursive
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
    mkdir -p build && cd build
    cmake .. && cmake --build . && mv prusa-console ../
fi
