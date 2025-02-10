#include <stdio.h>

#include "board.h"
#include "test.h"

int main(void) {
    printf("Running board implementation tests...\n\n");
    
    test_square_conversion();
    test_piece_manipulation();
    test_board_setup();
    test_fen();
    
    printf("\nAll tests passed!\n");
    
    // Display initial position
    Board board;
    board_init(&board);
    board_reset(&board);
    board_display(&board);
    
    return 0;
}