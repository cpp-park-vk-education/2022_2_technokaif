#!/usr/bin/env bash

cd ./server/build && ctest -V -R

#lcov -t "tests/tests_fib" -o coverage.info -c -d fib_lib/ 
#genhtml -o report coverage.info



