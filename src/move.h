#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>
#include <stdbool.h>

// Move flags (bits 14-15 of move value)
#define MOVE_FLAG_QUIET         0           // Regular move
#define MOVE_FLAG_CAPTURE       (1 << 14)   // Piece capture
#define MOVE_FLAG_PROMOTION     (2 << 14)   // Pawn promotion
#define MOVE_FLAG_SPECIAL       (3 << 14)   // Special moves (EP, castling)

// Special move flags (bits 16-17)
#define MOVE_SPECIAL_EP         (0 << 16)   // En passant capture
#define MOVE_SPECIAL_KCASTLE    (1 << 16)   // Kingside castle
#define MOVE_SPECIAL_QCASTLE    (2 << 16)   // Queenside castle
#define MOVE_SPECIAL_DOUBLE     (3 << 16)   // Double pawn push

// Promotion piece type flags (bits 16-18)
#define MOVE_PROMOTE_KNIGHT     (PIECE_KNIGHT<<16)
#define MOVE_PROMOTE_BISHOP     (PIECE_BISHOP<<16)
#define MOVE_PROMOTE_ROOK       (PIECE_ROOK<<16)
#define MOVE_PROMOTE_QUEEN      (PIECE_QUEEN<<16)

// Captured piece type (bits 19-21)
#define MOVE_CAPTURE_SHIFT      19

// Move masks for extracting fields
#define MOVE_FROM_MASK          0x7F        // Source square (7 bits)
#define MOVE_TO_MASK           (0x7F << 7)  // Target square (7 bits)
#define MOVE_FLAGS_MASK        (0x3 << 14)  // Basic move type (2 bits)
#define MOVE_SPECIAL_MASK      (0x3 << 16)  // Special move type (2 bits)
#define MOVE_PROMOTE_MASK      (0x7 << 16)  // Promotion piece (3 bits)
#define MOVE_CAPTURE_MASK      (0x7 << 19)  // Captured piece (3 bits)

typedef uint32_t Move;

// Move creation macro - validates squares first
#define MOVE_MAKE(from, to, flags) \
    ((uint8_t)(from) >= BOARD_SIZE_0x88 || INVALID_SQUARE((from)) || \
     (uint8_t)(to) >= BOARD_SIZE_0x88 || INVALID_SQUARE((to)) ? \
        0 : ((Move)(from) | ((Move)(to) << 7) | (Move)(flags)))

// Move extraction macros
#define MOVE_FROM(move)         ((move) & MOVE_FROM_MASK)
#define MOVE_TO(move)           (((move) & MOVE_TO_MASK) >> 7)
#define MOVE_FLAGS(move)        ((move) & MOVE_FLAGS_MASK)
#define MOVE_SPECIAL(move)      (((move) & MOVE_SPECIAL_MASK) >> 16)
#define MOVE_PROMOTION(move)    (((move) & MOVE_PROMOTE_MASK) >> 16)
#define MOVE_CAPTURED(move)     (((move) & MOVE_CAPTURE_MASK) >> 19)

// Move type checking
#define MOVE_IS_QUIET(move)     (MOVE_FLAGS(move) == MOVE_FLAG_QUIET)
#define MOVE_IS_CAPTURE(move)   (MOVE_FLAGS(move) == MOVE_FLAG_CAPTURE)
#define MOVE_IS_PROMOTION(move) (MOVE_FLAGS(move) == MOVE_FLAG_PROMOTION)
#define MOVE_IS_SPECIAL(move)   (MOVE_FLAGS(move) == MOVE_FLAG_SPECIAL)

#define MOVE_IS_EP(move)        (MOVE_IS_SPECIAL(move) && MOVE_SPECIAL(move) == MOVE_SPECIAL_EP)
#define MOVE_IS_KCASTLE(move)   (MOVE_IS_SPECIAL(move) && MOVE_SPECIAL(move) == MOVE_SPECIAL_KCASTLE)
#define MOVE_IS_QCASTLE(move)   (MOVE_IS_SPECIAL(move) && MOVE_SPECIAL(move) == MOVE_SPECIAL_QCASTLE)
#define MOVE_IS_DOUBLE(move)    (MOVE_IS_SPECIAL(move) && MOVE_SPECIAL(move) == MOVE_SPECIAL_DOUBLE)

// Function prototypes
const char* move_to_string(Move move, char* str);
Move move_from_string(const char* str);
bool move_is_valid(Move move);

#endif // MOVE_H