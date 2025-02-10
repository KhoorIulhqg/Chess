#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // size_t

// Piece definitions
#define PIECE_NONE      0
#define PIECE_PAWN      1
#define PIECE_KNIGHT    2
#define PIECE_BISHOP    3
#define PIECE_ROOK      4
#define PIECE_QUEEN     5
#define PIECE_KING      6

#define COLOR_WHITE     0
#define COLOR_BLACK     128
#define COLOR_MASK      128
#define PIECE_MASK      7

// Board size and invalid square detection
#define BOARD_SIZE      128
#define INVALID_SQUARE(sq)  ((sq) & 0x88)

// Piece manipulation macros
#define MAKE_PIECE(color, type)   ((color) | (type))
#define GET_PIECE_TYPE(piece)     ((piece) & PIECE_MASK)
#define GET_PIECE_COLOR(piece)    ((piece) & COLOR_MASK)
#define IS_PIECE_COLOR(piece, color) (GET_PIECE_COLOR(piece) == (color))

typedef struct {
    uint8_t squares[BOARD_SIZE];  // 0x88 board representation
    uint8_t side_to_move;         // COLOR_WHITE or COLOR_BLACK
    
    // Additional state will be added as needed
    uint8_t king_square[2];       // Track king positions for each side
} Board;

// Core board functions
void board_init(Board *board);
void board_reset(Board *board);
void board_clear(Board *board);

// Square conversion utilities
int coord_to_square(int file, int rank);
void square_to_coord(int square, int *file, int *rank);
bool is_valid_square(int square);

// Piece placement and query
void board_set_piece(Board *board, int square, uint8_t piece);
uint8_t board_get_piece(const Board *board, int square);
bool board_is_empty(const Board *board, int square);

// Display functions
void board_display(const Board *board);
const char *piece_to_char(uint8_t piece);

// FEN functions
bool board_set_fen(Board *board, const char *fen);
void board_get_fen(const Board *board, char *fen, size_t len);

#endif // BOARD_H