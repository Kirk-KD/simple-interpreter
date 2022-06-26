#include <iostream>

#include "interpreter.h"
#include "exception.h"

int main() {
    Parser parser("1 + (3 - 3)"); // inaccurate float, add double later
    Interpreter interpreter;

    try {
        node_p n = parser.parse();
        std::cout << node_to_string(*n) << std::endl;
        std::cout << interpreter.visit(n).to_string() << std::endl;
    } catch (Exception& e) {
        std::cout << e.what() << std::endl;
    }
}
