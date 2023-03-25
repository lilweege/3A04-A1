#!/usr/bin/env bash

# If building on windows with MinGW/Cygwin, remove -fsanitize to avoid link errors
CFLAGS="-std=c++20 -march=native -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror -fsanitize=undefined,address"

set -xe

g++ $CFLAGS src/*.cpp -o A1.out

