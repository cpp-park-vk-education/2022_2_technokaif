#!/usr/bin/env bash

set -o pipefail

function print_lint_header() {
    echo -e "\n***** ${1} *****"
}

print_lint_header "CLIENT CHECKS"

print_lint_header "CPPCHECK"
cppcheck client/src/* --enable=all --inconclusive --error-exitcode=1 -I./client/include --suppress=missingIncludeSystem

print_lint_header "CLANG-TIDY"
clang-tidy client/src/* -warnings-as-errors=* -extra-arg=-std=c++17 -- -Iclient/include

print_lint_header "CPPLINT"
cpplint --extensions=cpp /client/include /client/src

print_lint_header "SUCCESS"
