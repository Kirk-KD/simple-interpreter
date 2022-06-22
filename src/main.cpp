#include <iostream>

#include "parser.h"

int main() {
    Parser parser("5 + 1 * 2 - 3");
    std::cout << node_to_string(*parser.parse()) << std::endl;  
}
