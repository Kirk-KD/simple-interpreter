#include <iostream>

#include "parser.h"
#include "exception.h"

int main() {
    Parser parser("1 + 2");

    try {
        std::cout << node_to_string(*parser.parse()) << std::endl;
    } catch (Exception& e) {
        std::cout << e.what() << std::endl;
    }
}
