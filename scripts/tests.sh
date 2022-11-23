#!/usr/bin/env bash

path=$(pwd)
# server
cd ./server/build && ctest -V -R

lcov -t "tests/" -o coverage.info -c -d net/
genhtml -o report coverage.info
