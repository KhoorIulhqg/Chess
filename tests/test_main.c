#include "test.h"
#include "test_board.h"

#include <stdio.h>

int main(void) {
    printf("\n╔════════════════════════════════════════╗");
    printf("\n║         Running test suite ...         ║");
    printf("\n╚════════════════════════════════════════╝\n\n");
    
    run_board_tests();
    
    return 0;
}