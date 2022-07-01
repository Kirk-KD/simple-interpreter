#include <iostream>
#include <fstream>
#include <streambuf>

#include "interpreter.h"
#include "exception.h"
#include "test/test_runner.h"

int main() {
    // run_tests();

    std::ifstream input_file("examples/1.simp");
    std::string content = std::string(std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>());

    Parser parser(content);
    Interpreter interpreter;

    try {
        node_p n = parser.parse();
        std::cout << node_to_string(*n) << std::endl;
        std::cout << interpreter.visit(n).to_string() << std::endl;
    } catch (Exception& e) {
        std::cout << e.what() << std::endl;
    }
}
