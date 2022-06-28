#include "test/test_runner.h"

void run_eval_cases() {
    for (unsigned int i = 0; i < EVAL_CASES_SIZE; ++i) {
        std::cout << fmt::format("TEST CASE #{}: {}: ", i + 1, EVAL_CASES[i].name);

        try {
            Parser parser(EVAL_CASES[i].code);
            Interpreter interpreter;
            VisitResult result = interpreter.visit(parser.parse());

            if (result.type == EVAL_CASES[i].res_type) {
                switch (result.type) {
                    case value_type::int_t:
                        if (result.value_i != EVAL_CASES[i].res_i) {
                            std::cout << fmt::format("FAILED: {} expected, got {}", EVAL_CASES[i].res_i, result.value_i) << std::endl;
                            return;
                        }
                        break;
                    case value_type::float_t:
                        if (result.value_f != EVAL_CASES[i].res_f) {
                            std::cout << fmt::format("FAILED: {} expected, got {}", EVAL_CASES[i].res_f, result.value_f) << std::endl;
                            return;
                        }
                        break;
                    case value_type::double_t:
                        if (result.value_d != EVAL_CASES[i].res_d) {
                            std::cout << fmt::format("FAILED: {} expected, got {}", EVAL_CASES[i].res_d, result.value_d) << std::endl;
                            return;
                        }
                        break;
                    default:
                        std::cout << fmt::format("Unexpected type: {}", result.type);
                }
            } else {
                std::cout << fmt::format("FAILED: type {} expected, got {}", result.type, EVAL_CASES[i].res_type) << std::endl;
                return;
            }

            std::cout << "PASSED" << std::endl;
        } catch (Exception& e) {
            std::cout << "FAILED with error:" << std::endl;
            std::cout << e.what() << std::endl;
        }
    }
}

void run_tests() {
    run_eval_cases();
}
