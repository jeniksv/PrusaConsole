#!/bin/sh

mkdir -p build && cd build

curl -LOJ https://github.com/dbus-cxx/dbus-cxx/archive/refs/tags/2.4.0.tar.gz && tar -xf dbus-cxx-2.4.0.tar.gz
curl -LOJ https://download.gnome.org/sources/libsigc++/3.0/libsigc%2B%2B-3.0.0.tar.xz && tar -xf libsigc%2B%2B-3.0.0.tar.xz

cd libsigc++-3.0.0/build \
	&& cmake .. \
	&& make -j16 \
	&& sudo make install \
	&& cd ../..

mkdir -p dbus-cxx-2.4.0/build \
	&& cd dbus-cxx-2.4.0/build \
	&& cmake .. -DENABLE_TOOLS:BOOL=ON -DENABLE_EXAMPLES:BOOL=ON \
	&& make -j16 \
	&& sudo make install \
	&& cd ..

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
