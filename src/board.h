#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // size_t

// Physical Board definitions
#define BOARD_WIDTH_8x8     8
#define BOARD_HEIGHT_8x8    8
#define BOARD_SIZE_8x8      (BOARD_WIDTH_8x8 * BOARD_HEIGHT_8x8)

// Logical Board definitions
#define BOARD_SHIFT_0x88        4       // Used for 0x88 board
#define BOARD_RANK_MASK_0x88    0x07    // mask for getting rank from square
#define BOARD_WIDTH_0x88        16
#define BOARD_HEIGHT_0x88       8
#define BOARD_SIZE_0x88         (BOARD_WIDTH_0x88 * BOARD_HEIGHT_0x88)
#define INVALID_SQUARE(sq)      ((sq) & BOARD_SIZE_0x88)
#define NO_SQUARE               (-1) 

// Piece definitions
#define PIECE_NONE      0
#define PIECE_PAWN      1
#define PIECE_KNIGHT    2
#define PIECE_BISHOP    3
#define PIECE_ROOK      4
#define PIECE_QUEEN     5
#define PIECE_KING      6
#define PIECE_COUNT     7

#define COLOR_WHITE     0
#define COLOR_BLACK     128
#define COLOR_MASK      128
#define PIECE_MASK      7

// ASCII constants
#define ASCII_UPPER_OFFSET  32  // Difference between upper and lowercase ASCII

// FEN constants
#define FEN_MIN_LENGTH      24  // Minimum length for a valid FEN string

// Square conversion macros
#define SQUARE_TO_FILE(sq)  ((sq) & BOARD_RANK_MASK_0x88)
#define SQUARE_TO_RANK(sq)  ((sq) >> BOARD_SHIFT_0x88)
#define COORD_TO_SQUARE(f, r) ((r) * (1 << BOARD_SHIFT) + (f))


// Piece manipulation macros
#define MAKE_PIECE(color, type)         ((color) | (type))
#define GET_PIECE_TYPE(piece)           ((piece) & PIECE_MASK)
#define IS_PIECE_TYPE(piece, type)      (GET_PIECE_TYPE(piece) == (type))
#define GET_PIECE_COLOR(piece)          ((piece) & COLOR_MASK)
#define IS_PIECE_COLOR(piece, color)    (GET_PIECE_COLOR(piece) == (color))

// Castling rights
#define CASTLING_WHITE_KINGSIDE  (1 << 0)
#define CASTLING_WHITE_QUEENSIDE (1 << 1)
#define CASTLING_BLACK_KINGSIDE  (1 << 2)
#define CASTLING_BLACK_QUEENSIDE (1 << 3)

// Piece display index calculation
#define GET_PIECE_DISPLAY_INDEX(piece) \
    (GET_PIECE_TYPE(piece) + (IS_PIECE_COLOR(piece, COLOR_BLACK) ? PIECE_COUNT : 0))

// Piece display
#define PIECE_CHARS                 ".PNBRQK.pnbrqk"    // [none][white pieces][none][black pieces]
#define PIECE_TO_CHAR(piece)        PIECE_CHARS[GET_PIECE_DISPLAY_INDEX(piece)]
static const char *UNICODE_PIECES[] = {                 // must be strings due to multi-byte encoding :(
    ".", "♟", "♞", "♝", "♜", "♛", "♚",
    ".", "♙", "♘", "♗", "♖", "♕", "♔"
};
static inline const char *piece_to_unicode(uint8_t piece) {
    return UNICODE_PIECES[GET_PIECE_DISPLAY_INDEX(piece)];
}

typedef struct {
    uint8_t squares[BOARD_SIZE_0x88];   // 0x88 board representation
    uint8_t side_to_move;               // COLOR_WHITE or COLOR_BLACK
    uint8_t king_square[2];             // Track king positions for each side
    uint8_t castling_rights;            // Bitfield for castling availability
    int8_t en_passant_square;           // Square where en passant capture is possible (-1 if none)
    uint16_t halfmove_clock;            // Number of halfmoves since last capture or pawn advance
    uint16_t fullmove_number;           // Number of completed full moves
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

// Castling / En Pessant
void board_set_castling_rights(Board *board, uint8_t rights);
uint8_t board_get_castling_rights(const Board *board);
void board_set_en_passant_square(Board *board, int square);
int board_get_en_passant_square(const Board *board);

// FEN
bool board_set_fen(Board *board, const char *fen);
void board_get_fen(const Board *board, char *fen, size_t len);

#endif // BOARD_H