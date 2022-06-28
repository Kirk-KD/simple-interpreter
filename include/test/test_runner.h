#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <iostream>
#include <iterator>

#include "fmt/core.h"
#include "test/cases.h"
#include "interpreter.h"

void run_eval_cases(eval_case cases[]);

void run_tests();

#endif