#!/bin/bash

find . \( -path ./Unity -o -path ./cmake-build-* \) -prune -type f -o -name '*.h' -exec clang-format -style=file -i {} \;
find . \( -path ./Unity -o -path ./cmake-build-* -o -path ./tests/tests.all.cpp \) -prune -type f -o -name '*.cpp' -exec clang-format -style=file -i {} \;
