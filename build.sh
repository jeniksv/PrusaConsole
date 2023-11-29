#!/bin/sh

if [ "$1" = "--clean" ]; then
	rm -rf build/
else
	mkdir -p build && cd build
	cmake .. && cmake --build . && mv prusa-console ../
fi
