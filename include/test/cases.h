#ifndef CASES_H
#define CASES_H

#include <string>

#include "token.h"

struct eval_case {
    std::string name;
    std::string code;
    int res_i;
    float res_f;
    double res_d;
    value_type res_type;
};

inline static const eval_case EVAL_CASES[] = {
    eval_case{
        "bin_op",
        "1 + 1.5 - 1d - 100 * 2. / 10 + 100",
        0, 0, 81.5, value_type::double_t
    },
    eval_case{
        "unary_op",
        "---++-+-1.6 + ---+2. - -++--+++++++-1.009 * -1-1--1",
        0, -2.591, 0, value_type::float_t
    }
};

inline static const unsigned int EVAL_CASES_SIZE = sizeof(EVAL_CASES) / sizeof(EVAL_CASES[0]);

#endif