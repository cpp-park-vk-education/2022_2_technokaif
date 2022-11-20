#!/usr/bin/env bash

path=$(pwd)
# server
cd ./server/build && ctest -V -R

lcov -t "tests/tests_logic" -o coverage.info -c -d logic/
genhtml -o report coverage.info

cd path
# client
cd ./client/build && ctest -V -R

lcov -t "tests/tests_logic" -o coverage.info -c -d logic/
genhtml -o report coverage.info