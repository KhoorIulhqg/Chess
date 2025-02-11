#include "test.h"
#include "test_board.h"
#include "test_move.h"

#include <stdio.h>

int main(void) {
    printf("\n==========================================");
    printf("\n          Running test suite ...          ");
    printf("\n==========================================\n");
    
    run_board_tests();
    run_move_tests();
    
    printf("\n==========================================");
    printf("\n         Completed test suite ...         ");
    printf("\n==========================================\n\n");

    return 0;
}