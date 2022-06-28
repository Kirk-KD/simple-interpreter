#include <iostream>

#include "interpreter.h"
#include "exception.h"
#include "test/test_runner.h"

int main() {
    // run_tests();

    Parser parser("1 + 1; 2 - 4; 0.3 * 0.4; 0.1d - 6.9;");
    Interpreter interpreter;

    try {
        node_p n = parser.parse();
        std::cout << node_to_string(*n) << std::endl;
        std::cout << interpreter.visit(n).to_string() << std::endl;
    } catch (Exception& e) {
        std::cout << e.what() << std::endl;
    }
}
