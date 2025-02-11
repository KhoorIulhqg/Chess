#include <stdio.h>

#include "board.h"
#include "test.h"

int main(void) {
    printf("\n╔════════════════════════════════════════╗\n");
    printf("║          Chess Engine v0.1.0           ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
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