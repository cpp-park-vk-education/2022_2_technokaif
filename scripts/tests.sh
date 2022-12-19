#!/usr/bin/env bash

function print_header() {
    echo -e "\n***** ${1} *****"
}

path=$(pwd)

# SERVER
print_header "RUNNING TESTS"
cd ./server/build && ctest -V -R

print_header "GENERATING COVERAGE INFO"
lcov -t "tests/" -o coverage.info -c -d net/ -d logic/
lcov --remove coverage.info '/usr/*' '*/boost/*' -o filtered_coverage.info

print_header "COVERAGE REPORT"
genhtml -o report filtered_coverage.info
