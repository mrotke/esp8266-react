#!/bin/bash

apt install libmicrohttpd #install libmicrohttpd deamon

#get and install libhttpserver
git clone https://github.com/etr/libhttpserver.git
cd libhttpserver
./bootstrap
mkdir build
cd build
../configure
make
make install
cd ..
cd ..


#get and install mbedTLS
git clone https://github.com/Mbed-TLS/mbedtls.git
cd mbedtls
git checkout v3.1.0
make
make install
