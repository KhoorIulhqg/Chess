#include "test_board.h"

#include <assert.h>
#include <stdio.h>
#include <string.h> // strcmp()

#include "test.h"
#include "../src/board.h"

INIT_TEST_SUITE(BOARD_TESTS);

void run_board_tests(void) {
    TEST_SUITE(BOARD_TESTS);

    TEST_CASE(BOARD_TESTS, "Square conversion") {
        uint8_t file, rank;

        // Test some key squares
        ASSERT(BOARD_TESTS, COORD_TO_SQUARE(0, 0) == 0);    // a1
        ASSERT(BOARD_TESTS, COORD_TO_SQUARE(7, 7) == 119);  // h8

        square_to_coord(0, &file, &rank);
        ASSERT(BOARD_TESTS, file == 0 && rank == 0);
        
        square_to_coord(119, &file, &rank);
        ASSERT(BOARD_TESTS, file == 7 && rank == 7);
    } END_TEST_CASE(BOARD_TESTS);

    TEST_CASE(BOARD_TESTS, "Piece Manipulation") {
        static const uint8_t white_pawn = MAKE_PIECE(COLOR_WHITE, PIECE_PAWN);
        static const uint8_t black_king = MAKE_PIECE(COLOR_BLACK, PIECE_KING);
    
        ASSERT(BOARD_TESTS, GET_PIECE_TYPE(white_pawn) == PIECE_PAWN);
        ASSERT(BOARD_TESTS, GET_PIECE_COLOR(white_pawn) == COLOR_WHITE);
        
        ASSERT(BOARD_TESTS, GET_PIECE_TYPE(black_king) == PIECE_KING);
        ASSERT(BOARD_TESTS, GET_PIECE_COLOR(black_king) == COLOR_BLACK);
        
        ASSERT(BOARD_TESTS, IS_PIECE_COLOR(white_pawn, COLOR_WHITE));
        ASSERT(BOARD_TESTS, !IS_PIECE_COLOR(black_king, COLOR_WHITE));
    } END_TEST_CASE(BOARD_TESTS);

    TEST_CASE(BOARD_TESTS, "Board Setup") {
        Board board;
    
        // Test initial position
        board_init(&board);
        board_reset(&board);
        
        // Check some key squares
        ASSERT(BOARD_TESTS, GET_PIECE_TYPE(board_get_piece(&board, COORD_TO_SQUARE(0, 0))) == PIECE_ROOK);
        ASSERT(BOARD_TESTS, GET_PIECE_TYPE(board_get_piece(&board, COORD_TO_SQUARE(4, 0))) == PIECE_KING);
        ASSERT(BOARD_TESTS, GET_PIECE_TYPE(board_get_piece(&board, COORD_TO_SQUARE(3, 7))) == PIECE_QUEEN);
        
        // Test king tracking
        ASSERT(BOARD_TESTS, board.king_square[0] == COORD_TO_SQUARE(4, 0));  // White king
        ASSERT(BOARD_TESTS, board.king_square[1] == COORD_TO_SQUARE(4, 7));  // Black king
    } END_TEST_CASE(BOARD_TESTS);

    TEST_CASE(BOARD_TESTS, "FEN conversion") {
        Board board;
        char fen[100];
        
        // Test case 1: Initial position with all castling rights
        const char *initial_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
        ASSERT(BOARD_TESTS, board_set_fen(&board, initial_fen));
        ASSERT(BOARD_TESTS, board.castling_rights == (CASTLING_WHITE_KINGSIDE | CASTLING_WHITE_QUEENSIDE | 
                                       CASTLING_BLACK_KINGSIDE | CASTLING_BLACK_QUEENSIDE));
        ASSERT(BOARD_TESTS, board.en_passant_square == -1);
        board_get_fen(&board, fen, sizeof(fen));
        ASSERT(BOARD_TESTS, strcmp(fen, initial_fen) == 0);
        
        // Test case 2: Position with partial castling rights and en passant
        const char *advanced_fen = "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQk e6 0 2";
        ASSERT(BOARD_TESTS, board_set_fen(&board, advanced_fen));
        ASSERT(BOARD_TESTS, board.castling_rights == (CASTLING_WHITE_KINGSIDE | CASTLING_WHITE_QUEENSIDE | 
                                       CASTLING_BLACK_KINGSIDE));
        ASSERT(BOARD_TESTS, board.en_passant_square == COORD_TO_SQUARE(4, 5));  // e6 square
        board_get_fen(&board, fen, sizeof(fen));
        ASSERT(BOARD_TESTS, strcmp(fen, advanced_fen) == 0);
        
        // Test case 3: Position with no castling rights or en passant
        const char *mid_fen = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w - - 0 1";
        ASSERT(BOARD_TESTS, board_set_fen(&board, mid_fen));
        ASSERT(BOARD_TESTS, board.castling_rights == 0);
        ASSERT(BOARD_TESTS, board.en_passant_square == -1);
        board_get_fen(&board, fen, sizeof(fen));
        ASSERT(BOARD_TESTS, strcmp(fen, mid_fen) == 0);
        
        // Test case 4: Position after kingside castling
        const char *castled_fen = "rnbq1rk1/pppp1ppp/5n2/2b1p3/2B1P3/5N2/PPPP1PPP/RNBQK2R w KQ - 0 1";
        ASSERT(BOARD_TESTS, board_set_fen(&board, castled_fen));
        ASSERT(BOARD_TESTS, board.castling_rights == (CASTLING_WHITE_KINGSIDE | CASTLING_WHITE_QUEENSIDE));
        board_get_fen(&board, fen, sizeof(fen));
        ASSERT(BOARD_TESTS, strcmp(fen, castled_fen) == 0);
        
        // Test case 5: Position with en passant opportunity
        const char *ep_fen = "rnbqkbnr/ppp2ppp/4p3/3pP3/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3";
        ASSERT(BOARD_TESTS, board_set_fen(&board, ep_fen));
        ASSERT(BOARD_TESTS, board.en_passant_square == COORD_TO_SQUARE(3, 5));  // d6 square
        board_get_fen(&board, fen, sizeof(fen));
        ASSERT(BOARD_TESTS, strcmp(fen, ep_fen) == 0);
        
        // Test case 6: Endgame position with move counters
        const char *endgame_fen = "4k3/8/8/8/8/8/4P3/4K3 w - - 12 24";
        ASSERT(BOARD_TESTS, board_set_fen(&board, endgame_fen));
        ASSERT(BOARD_TESTS, board.halfmove_clock == 12);
        ASSERT(BOARD_TESTS, board.fullmove_number == 24);
        board_get_fen(&board, fen, sizeof(fen));
        ASSERT(BOARD_TESTS, strcmp(fen, endgame_fen) == 0);    
    } END_TEST_CASE(BOARD_TESTS);

    print_test_results(&BOARD_TESTS);
}