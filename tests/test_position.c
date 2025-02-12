#include "test_position.h"

#include <string.h>

#include "test.h"
#include "../src/position.h"

INIT_TEST_SUITE(POSITION_TESTS);

void run_position_tests(void) {
    TEST_SUITE(POSITION_TESTS);

    TEST_CASE(POSITION_TESTS, "Position key generation") {
        Position pos1, pos2;
        
        // Same position should generate same key
        position_reset(&pos1);
        position_reset(&pos2);
        uint32_t key1 = position_generate_key(&pos1);
        uint32_t key2 = position_generate_key(&pos2);
        ASSERT(POSITION_TESTS, key1 == key2);
        ASSERT(POSITION_TESTS, key1 == pos1.state_history[0].position_key);
        
        // Different positions should generate different keys
        board_set_piece(&pos2.board, COORD_TO_SQUARE(4, 1), PIECE_NONE); // Remove e2 pawn
        key2 = position_generate_key(&pos2);
        ASSERT(POSITION_TESTS, key1 != key2);
    } END_TEST_CASE(POSITION_TESTS);

    TEST_CASE(POSITION_TESTS, "Position comparison") {
        Position pos1, pos2;
        
        // Same position should compare equal
        position_reset(&pos1);
        position_reset(&pos2);
        ASSERT(POSITION_TESTS, position_compare(&pos1, &pos2));
        
        // Different positions should compare unequal
        board_set_piece(&pos2.board, COORD_TO_SQUARE(4, 1), PIECE_NONE);
        ASSERT(POSITION_TESTS, !position_compare(&pos1, &pos2));
        
        // Different state but same pieces should compare unequal
        position_reset(&pos2);
        pos2.board.side_to_move = COLOR_BLACK;
        ASSERT(POSITION_TESTS, !position_compare(&pos1, &pos2));
    } END_TEST_CASE(POSITION_TESTS);

    TEST_CASE(POSITION_TESTS, "Position validation") {
        Position pos;
        position_reset(&pos);
        
        // Initial position should be valid
        ASSERT(POSITION_TESTS, position_is_valid(&pos));
        
        // Invalid ply should fail validation
        pos.ply = MAX_PLY;
        ASSERT(POSITION_TESTS, !position_is_valid(&pos));
        
        // Invalid history count should fail validation
        position_reset(&pos);
        pos.history_count = pos.ply + 2;
        ASSERT(POSITION_TESTS, !position_is_valid(&pos));
        
        // Incorrect hash should fail validation
        position_reset(&pos);
        pos.state_history[0].position_key ^= 1;
        ASSERT(POSITION_TESTS, !position_is_valid(&pos));

        // Missing king should fail validation
        position_reset(&pos);
        board_set_piece(&pos.board, COORD_TO_SQUARE(4, 0), PIECE_NONE); // Remove white king
        ASSERT(POSITION_TESTS, !position_is_valid(&pos));

        // Extra king should fail validation
        position_reset(&pos);
        board_set_piece(&pos.board, COORD_TO_SQUARE(5, 0), MAKE_PIECE(COLOR_WHITE, PIECE_KING));
        ASSERT(POSITION_TESTS, !position_is_valid(&pos));

        // Invalid en passant square should fail validation
        position_reset(&pos);
        pos.state_history[0].en_passant_square = COORD_TO_SQUARE(3, 2); // Invalid rank for white
        pos.board.en_passant_square = COORD_TO_SQUARE(3, 2);
        ASSERT(POSITION_TESTS, !position_is_valid(&pos));

        // Invalid castling rights should fail validation
        position_reset(&pos);
        board_set_piece(&pos.board, COORD_TO_SQUARE(7, 0), PIECE_NONE); // Remove white kingside rook
        ASSERT(POSITION_TESTS, !position_is_valid(&pos));

        // Pawn on first rank should fail validation
        position_reset(&pos);
        board_set_piece(&pos.board, COORD_TO_SQUARE(0, 0), MAKE_PIECE(COLOR_WHITE, PIECE_PAWN));
        ASSERT(POSITION_TESTS, !position_is_valid(&pos));

        // Pawn on last rank should fail validation
        position_reset(&pos);
        board_set_piece(&pos.board, COORD_TO_SQUARE(0, 7), MAKE_PIECE(COLOR_BLACK, PIECE_PAWN));
        ASSERT(POSITION_TESTS, !position_is_valid(&pos));
    } END_TEST_CASE(POSITION_TESTS);

    print_test_results(&POSITION_TESTS);
}