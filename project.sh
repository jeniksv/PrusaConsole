#!/bin/sh

if [ "$1" = "--clean" ]; then
    rm -rf build/
    rm prusa-console
fi

if [ "$1" = "--test" ]; then
    mkdir -p build && cd build
    cmake .. && cmake --build . && ./tests
fi

if [ "$1" = "--build" ]; then
    mkdir -p build && cd build
    cmake .. && cmake --build . && mv prusa-console ../
fi

