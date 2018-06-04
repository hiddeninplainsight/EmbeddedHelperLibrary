#!/usr/bin/env bash

compile_and_strip () {
    arm-none-eabi-g++ -std=c++11 -O3 -S $1.cpp -o - | awk '!/\./' > $1.s
}

compile_and_strip code_size_add_int
compile_and_strip code_size_add_safe_type

compile_and_strip code_size_copy_int_collection
compile_and_strip code_size_copy_safe_type_collection
