#ifndef POSITION_H
#define POSITION_H

#include <stdbool.h>
#include <stdint.h>

#include "board.h"
#include "move.h"

// Maximum ply depth for search
#define MAX_PLY 40

// State information that needs to be stored/restored for unmake_move
typedef struct {
    uint32_t position_key;      // Incremental position hash
    uint8_t castling_rights;    // Current castling availability
    int8_t en_passant_square;   // Current en passant target square
    uint16_t halfmove_clock;    // Moves since last pawn move or capture
    uint8_t captured_piece;     // Piece captured in this position (if any)
} PositionState;

// Core position structure
typedef struct {
    Board board;                            // Current board state
    PositionState state_history[MAX_PLY];   // History for unmake_move
    Move moves[MAX_PLY];                    // History of moves made
    uint16_t ply;                           // Current position ply
    uint16_t history_count;                 // Number of positions in history
} Position;

// Core position management functions
void position_init(Position *pos);
void position_reset(Position *pos);
void position_clear(Position *pos);
uint32_t position_generate_key(const Position *pos);
bool position_set_fen(Position *pos, const char *fen);
void position_get_fen(const Position *pos, char *fen, uint8_t len);

// Move making/unmaking
bool position_make_move(Position *pos, Move move);
void position_unmake_move(Position *pos);

// Position key/validation
uint32_t position_generate_key(const Position *pos);
bool position_is_valid(const Position *pos);
bool position_compare(const Position *pos1, const Position *pos2);

// Display functions
void position_display(const Position *pos);
void position_display_history(const Position *pos);

#endif // POSITION_H