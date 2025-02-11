#include <stdio.h>

#include "board.h"

int main(void) {
    printf("\n╔════════════════════════════════════════╗");
    printf("\n║          Chess Engine v0.1.0           ║");
    printf("\n╚════════════════════════════════════════╝\n");
    
    // Display initial position
    Board board;
    board_init(&board);
    board_reset(&board);
    board_display(&board);
    
    return 0;
}