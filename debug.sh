#!/bin/bash

find ./src -name *.cpp | xargs echo "Compile & DEBUG:"
g++ -std=c++17 -I include -Wall -Wextra -Wconversion $(find ./src -name *.cpp) -ldpp -o ./bin/Simple_GDB -g
gdb ./bin/Simple_GDB