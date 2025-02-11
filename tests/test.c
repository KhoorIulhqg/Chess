#include "test.h"

#include <stdio.h>

void print_test_results(const TestSuite* suite) {
    printf("\n%s Results: %d/%d tests passed\n",
           suite->name,
           suite->tests_run - suite->tests_failed,
           suite->tests_run);
}