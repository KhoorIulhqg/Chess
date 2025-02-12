#ifndef ZOBRIST_H
#define ZOBRIST_H

#include <stdint.h>

// Zobrist hashing constants for pieces (color, piece type, square)
extern const uint32_t ZOBRIST_PIECES[2][7][64];

// Zobrist hashing constants for castling rights
extern const uint32_t ZOBRIST_CASTLING[16];

// Zobrist hashing constants for en passant file
extern const uint32_t ZOBRIST_EN_PASSANT[8];

// Zobrist hashing constant for side to move
extern const uint32_t ZOBRIST_SIDE_TO_MOVE;

#endif // ZOBRIST_H