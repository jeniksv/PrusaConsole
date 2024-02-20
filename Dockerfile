FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y \
    git \
    cmake \
    build-essential \
    pkg-config \
    libdbus-glib-1-dev \
    libgirepository1.0-dev \
    curl \
    libpopt-dev \
    libexpat1-dev \
    vim

RUN curl -LOJ https://download.gnome.org/sources/libsigc++/3.0/libsigc%2B%2B-3.0.0.tar.xz && \
    tar -xf libsigc%2B%2B-3.0.0.tar.xz && \
    cd libsigc++-3.0.0 && \
    mkdir -p build && cd build && \
    cmake .. && \
    make -j16 && \
    make install && \
    cd ../..

RUN curl -LOJ https://github.com/dbus-cxx/dbus-cxx/archive/refs/tags/2.4.0.tar.gz -o dbus-cxx-2.4.0.tar.gz && \
    tar -xf dbus-cxx-2.4.0.tar.gz && \
    cd dbus-cxx-2.4.0 && \
    mkdir -p build && cd build && \
    cmake .. -DENABLE_TOOLS:BOOL=ON -DENABLE_EXAMPLES:BOOL=ON && \
    make -j16 && \
    make install && \
    cd ../..
    #export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib

WORKDIR /app

COPY . /app

RUN cmake .

#CMD ["/app/prusa-console"]

