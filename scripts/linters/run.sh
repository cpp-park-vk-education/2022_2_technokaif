#!/usr/bin/env bash

set -o pipefail

function print_lint_header() {
    echo -e "\n***** ${1} *****"
}

print_lint_header "SERVER CHECKS"
print_lint_header "CPPCHECK"
cppcheck ./server --enable=all --inconclusive --error-exitcode=1 -I./server/logic/include --suppress=missingIncludeSystem
# cppcheck ./server --enable=all --inconclusive --error-exitcode=1 -I./server/net/include  --suppress=missingIncludeSystem

print_lint_header "CLANG-TIDY"
clang-tidy server/logic/src/* server/logic/include/* -warnings-as-errors=* -extra-arg=-std=c++17 -- -Iserver/logic/include
clang-tidy server/net/src/* server/net/include/* -warnings-as-errors=* -extra-arg=-std=c++17 -- -Iserver/net/include

print_lint_header "CPPLINT"
cpplint --extensions=cpp ./server/logic/include/* ./server/logic/src/*
cpplint --extensions=cpp ./server/net/include/* ./server/net/src/*

print_lint_header "SUCCESS"
