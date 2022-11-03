#!/usr/bin/env bash

VALGRIND_LOG="valgrind.log"

valgrind --tool=memcheck --leak-check=summary --leak-check=full --track-origins=yes --log-file=${VALGRIND_LOG} "$@" || exit 1

cat ${VALGRIND_LOG}
