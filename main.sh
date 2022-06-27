#!/bin/bash

find ./src -name *.cpp | xargs echo "Compile:"
g++ -std=c++17 -I include -Wall -Wextra -Wconversion $(find ./src -name *.cpp) -ldpp -o ./bin/Simple
./bin/Simple
