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
    
    // Test case 1: Initial position with all castling rights
    const char *initial_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    assert(board_set_fen(&board, initial_fen));
    assert(board.castling_rights == (CASTLING_WHITE_KINGSIDE | CASTLING_WHITE_QUEENSIDE | 
                                   CASTLING_BLACK_KINGSIDE | CASTLING_BLACK_QUEENSIDE));
    assert(board.en_passant_square == -1);
    board_get_fen(&board, fen, sizeof(fen));
    assert(strcmp(fen, initial_fen) == 0);
    
    // Test case 2: Position with partial castling rights and en passant
    const char *advanced_fen = "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQk e6 0 2";
    assert(board_set_fen(&board, advanced_fen));
    assert(board.castling_rights == (CASTLING_WHITE_KINGSIDE | CASTLING_WHITE_QUEENSIDE | 
                                   CASTLING_BLACK_KINGSIDE));
    assert(board.en_passant_square == coord_to_square(4, 5));  // e6 square
    board_get_fen(&board, fen, sizeof(fen));
    assert(strcmp(fen, advanced_fen) == 0);
    
    // Test case 3: Position with no castling rights or en passant
    const char *mid_fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w - - 0 1";
    assert(board_set_fen(&board, mid_fen));
    assert(board.castling_rights == 0);
    assert(board.en_passant_square == -1);
    board_get_fen(&board, fen, sizeof(fen));
    assert(strcmp(fen, mid_fen) == 0);
    
    // Test case 4: Position after kingside castling
    const char *castled_fen = "rnbq1rk1/pppp1ppp/5n2/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQ - 0 1";
    assert(board_set_fen(&board, castled_fen));
    assert(board.castling_rights == (CASTLING_WHITE_KINGSIDE | CASTLING_WHITE_QUEENSIDE));
    board_get_fen(&board, fen, sizeof(fen));
    assert(strcmp(fen, castled_fen) == 0);
    
    // Test case 5: Position with en passant opportunity
    const char *ep_fen = "rnbqkbnr/ppp2ppp/4p3/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3";
    assert(board_set_fen(&board, ep_fen));
    assert(board.en_passant_square == coord_to_square(3, 5));  // d6 square
    board_get_fen(&board, fen, sizeof(fen));
    assert(strcmp(fen, ep_fen) == 0);
    
    // Test case 6: Endgame position with move counters
    const char *endgame_fen = "4k3/8/8/8/8/8/4P3/4K3 w - - 12 24";
    assert(board_set_fen(&board, endgame_fen));
    assert(board.halfmove_clock == 12);
    assert(board.fullmove_number == 24);
    board_get_fen(&board, fen, sizeof(fen));
    assert(strcmp(fen, endgame_fen) == 0);
    
    printf("FEN tests passed!\n");
}