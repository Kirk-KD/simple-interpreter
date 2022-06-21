#include <iostream>

#include "parser.h"

int main() {
    Parser parser("1");
    std::cout << node_to_string(*parser.parse()) << std::endl;
}
