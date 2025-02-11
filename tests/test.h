#ifndef TEST_H
#define TEST_H

#include <stdbool.h>

typedef struct {
    const char* name;
    unsigned int tests_run;
    unsigned int tests_failed;
} TestSuite;

// Core test framework declarations
extern TestSuite BOARD_TESTS;
extern TestSuite MOVE_TESTS;

// Test suite initializer macro
#define INIT_TEST_SUITE(name) TestSuite name = {#name, 0, 0}

// Test macros
#define TEST_SUITE(suite) \
    printf("\nRunning %s...\n", suite.name); \
    suite.tests_run = 0; \
    suite.tests_failed = 0; \
    unsigned int test_counter = 0

#define TEST_CASE(suite, name) \
    do { \
        printf("  %s: ", name); \
        suite.tests_run++; \
        test_counter++; \
        bool test_failed = false; \
        { \
            bool* const curr_test = &test_failed;

#define END_TEST_CASE(suite) \
        } \
        if (test_failed) { \
            suite.tests_failed++; \
            printf("FAILED\n"); \
        } else { \
            printf("passed\n"); \
        } \
    } while(0)

#define ASSERT(suite, condition) \
    do { \
        if (!(condition)) { \
            *curr_test = true; \
            printf("\n    Assertion failed: %s\n    File %s, Line %d\n", \
                   #condition, __FILE__, __LINE__); \
        } \
    } while(0)

// Framework functions
void print_test_results(const TestSuite* suite);

#endif // TEST_H
