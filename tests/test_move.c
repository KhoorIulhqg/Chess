#include "test_move.h"

#include <stdio.h>
#include <string.h> // strcmp()

#include "test.h"
#include "../src/board.h"
#include "../src/move.h"

INIT_TEST_SUITE(MOVE_TESTS);

void run_move_tests(void) {
    TEST_SUITE(MOVE_TESTS);

    TEST_CASE(MOVE_TESTS, "Piece encoding") {
        // Test basic move encoding/decoding
        Move m1 = MOVE_MAKE(0x00, 0x10, MOVE_FLAG_QUIET); // a1 to a2
        ASSERT(MOVE_TESTS, MOVE_FROM(m1) == 0x00);
        ASSERT(MOVE_TESTS, MOVE_TO(m1) == 0x10);
        ASSERT(MOVE_TESTS, MOVE_IS_QUIET(m1));
        ASSERT(MOVE_TESTS, !MOVE_IS_CAPTURE(m1));
        ASSERT(MOVE_TESTS, !MOVE_IS_PROMOTION(m1));

        // Test capture move
        Move m2 = MOVE_MAKE(0x61, 0x52, MOVE_FLAG_CAPTURE | (PIECE_PAWN << 19)); // g2 takes f3
        ASSERT(MOVE_TESTS, MOVE_FROM(m2) == 0x61);
        ASSERT(MOVE_TESTS, MOVE_TO(m2) == 0x52);
        ASSERT(MOVE_TESTS, MOVE_IS_CAPTURE(m2));
        ASSERT(MOVE_TESTS, MOVE_CAPTURED(m2) == PIECE_PAWN);

        // Test promotion move
        Move m3 = MOVE_MAKE(0x70, 0x71, MOVE_FLAG_PROMOTION | MOVE_PROMOTE_QUEEN); // h7 to h8=Q
        ASSERT(MOVE_TESTS, MOVE_FROM(m3) == 0x70);
        ASSERT(MOVE_TESTS, MOVE_TO(m3) == 0x71);
        ASSERT(MOVE_TESTS, MOVE_IS_PROMOTION(m3));
        ASSERT(MOVE_TESTS, MOVE_PROMOTION(m3) == PIECE_QUEEN);
    } END_TEST_CASE(MOVE_TESTS);

    TEST_CASE(MOVE_TESTS, "Move string conversion") {
        char str[6];
    
        // Test basic move
        Move m1 = MOVE_MAKE(COORD_TO_SQUARE(4, 1), COORD_TO_SQUARE(4, 3), MOVE_FLAG_QUIET);
        move_to_string(m1, str);
        ASSERT(MOVE_TESTS, strcmp(str, "e2e4") == 0);
        ASSERT(MOVE_TESTS, move_from_string("e2e4") == m1);
        
        // Test promotion
        Move m2 = MOVE_MAKE(COORD_TO_SQUARE(0, 6), COORD_TO_SQUARE(0, 7), 
                           MOVE_FLAG_PROMOTION | MOVE_PROMOTE_QUEEN);
        move_to_string(m2, str);
        ASSERT(MOVE_TESTS, strcmp(str, "a7a8q") == 0);
        ASSERT(MOVE_TESTS, move_from_string("a7a8q") == m2);
        
        // Test invalid moves
        ASSERT(MOVE_TESTS, move_from_string("") == 0);
        ASSERT(MOVE_TESTS, move_from_string("e2") == 0);
        ASSERT(MOVE_TESTS, move_from_string("e2e9") == 0);
        ASSERT(MOVE_TESTS, move_from_string("e2e4q") == 0); // Not a promotion square
    } END_TEST_CASE(MOVE_TESTS);

    TEST_CASE(MOVE_TESTS, "Move validation") {
        // Test valid moves
        Move m1 = MOVE_MAKE(0x00, 0x10, MOVE_FLAG_QUIET);
        ASSERT(MOVE_TESTS, move_is_valid(m1));

        Move m2 = MOVE_MAKE(COORD_TO_SQUARE(4, 6), COORD_TO_SQUARE(4, 7),
                        MOVE_FLAG_PROMOTION | MOVE_PROMOTE_QUEEN);
        ASSERT(MOVE_TESTS, move_is_valid(m2));

        // Test invalid moves
        Move m3 = MOVE_MAKE(0x88, 0x00, MOVE_FLAG_QUIET); // Invalid from square
        ASSERT(MOVE_TESTS, !move_is_valid(m3));

        Move m4 = MOVE_MAKE(0x00, 0x00, MOVE_FLAG_QUIET); // Same square
        ASSERT(MOVE_TESTS, !move_is_valid(m4));

        Move m5 = MOVE_MAKE(0x00, 0x10, MOVE_FLAG_PROMOTION | (PIECE_PAWN << 16)); // Invalid promotion piece
        ASSERT(MOVE_TESTS, !move_is_valid(m5));
    } END_TEST_CASE(MOVE_TESTS);

    print_test_results(&MOVE_TESTS);
}
