#!/usr/bin/env bash

COMPILE="arm-linux-gnueabi-g++-5 -std=c++11 -O3 -S"

${COMPILE} code_size_add_int.cpp
${COMPILE} code_size_add_safe_type.cpp

${COMPILE} code_size_copy_int_collection.cpp
${COMPILE} code_size_copy_safe_type_collection.cpp
