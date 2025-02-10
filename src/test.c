#include "test.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_square_conversion(void) {
    int file, rank;
    
    // Test some key squares
    assert(coord_to_square(0, 0) == 0);  // a1
    assert(coord_to_square(7, 7) == 119); // h8
    
    square_to_coord(0, &file, &rank);
    assert(file == 0 && rank == 0);
    
    square_to_coord(119, &file, &rank);
    assert(file == 7 && rank == 7);
    
    printf("Square conversion tests passed!\n");
}

void test_piece_manipulation(void) {
    uint8_t white_pawn = MAKE_PIECE(COLOR_WHITE, PIECE_PAWN);
    uint8_t black_king = MAKE_PIECE(COLOR_BLACK, PIECE_KING);
    
    assert(GET_PIECE_TYPE(white_pawn) == PIECE_PAWN);
    assert(GET_PIECE_COLOR(white_pawn) == COLOR_WHITE);
    
    assert(GET_PIECE_TYPE(black_king) == PIECE_KING);
    assert(GET_PIECE_COLOR(black_king) == COLOR_BLACK);
    
    assert(IS_PIECE_COLOR(white_pawn, COLOR_WHITE));
    assert(!IS_PIECE_COLOR(black_king, COLOR_WHITE));
    
    printf("Piece manipulation tests passed!\n");
}

void test_board_setup(void) {
    Board board;
    
    // Test initial position
    board_init(&board);
    board_reset(&board);
    
    // Check some key squares
    assert(GET_PIECE_TYPE(board_get_piece(&board, coord_to_square(0, 0))) == PIECE_ROOK);
    assert(GET_PIECE_TYPE(board_get_piece(&board, coord_to_square(4, 0))) == PIECE_KING);
    assert(GET_PIECE_TYPE(board_get_piece(&board, coord_to_square(3, 7))) == PIECE_QUEEN);
    
    // Test king tracking
    assert(board.king_square[0] == coord_to_square(4, 0));  // White king
    assert(board.king_square[1] == coord_to_square(4, 7));  // Black king
    
    printf("Board setup tests passed!\n");
}

void test_fen(void) {
    Board board;
    char fen[100];
    
    // Test case 1: Initial position
    assert(board_set_fen(&board, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1"));
    board_get_fen(&board, fen, sizeof(fen));
    assert(strcmp(fen, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w - - 0 1") == 0);
    
    // Test case 2: Complex middlegame position
    const char *test_fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w - - 0 1";
    assert(board_set_fen(&board, test_fen));
    board_get_fen(&board, fen, sizeof(fen));
    assert(strcmp(fen, test_fen) == 0);
    
    // Test case 3: Empty board
    assert(board_set_fen(&board, "8/8/8/8/8/8/8/8 w - - 0 1"));
    board_get_fen(&board, fen, sizeof(fen));
    assert(strcmp(fen, "8/8/8/8/8/8/8/8 w - - 0 1") == 0);
    
    // Test case 4: Asymmetric position
    const char *asym_fen = "rnb1k1nr/pp1p1ppp/1qp5/4p3/2B1P3/2N2N2/PPPP1PPP/R1BQK2R b - - 0 1";
    assert(board_set_fen(&board, asym_fen));
    board_get_fen(&board, fen, sizeof(fen));
    assert(strcmp(fen, asym_fen) == 0);
    
    // Test case 5: Endgame position
    const char *end_fen = "4k3/8/8/8/8/8/4P3/4K3 w - - 0 1";
    assert(board_set_fen(&board, end_fen));
    board_get_fen(&board, fen, sizeof(fen));
    assert(strcmp(fen, end_fen) == 0);
    
    // Verify key piece positions in complex position
    assert(board_set_fen(&board, test_fen));
    assert(GET_PIECE_TYPE(board_get_piece(&board, coord_to_square(4, 0))) == PIECE_KING);   // e1
    assert(GET_PIECE_TYPE(board_get_piece(&board, coord_to_square(4, 4))) == PIECE_KNIGHT); // e5
    
    printf("FEN tests passed!\n");
}