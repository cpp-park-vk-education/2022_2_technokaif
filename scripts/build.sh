#!/usr/bin/env bash

path=$(pwd)

# cd server
# mkdir build
# cd build
# cmake "$@" ..
# cmake --build .

cd $path
touch config.ovpn
cd client
mkdir build
cd build
cmake "$@" ..
cmake --build .
