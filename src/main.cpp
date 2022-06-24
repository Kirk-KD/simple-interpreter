#include <iostream>

#include "interpreter.h"
#include "exception.h"

int main() {
    Parser parser("0.51 - 2400"); // inaccurate float, add double later
    Interpreter interpreter;

    try {
        node_p n = parser.parse();
        std::cout << interpreter.visit(n).to_string() << std::endl;
    } catch (Exception& e) {
        std::cout << e.what() << std::endl;
    }
}
