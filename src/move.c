#include "move.h"

#include <stdio.h>
#include <string.h> // strlen()
#include <ctype.h> // tolower()

#include "board.h"

// Convert a move to algebraic notation (e.g. "e2e4", "e7e8q")

const char* move_to_string(Move move, char* str) {
    if (!str) return NULL;
    
    uint8_t from_file = SQUARE_TO_FILE(MOVE_FROM(move));
    uint8_t from_rank = SQUARE_TO_RANK(MOVE_FROM(move));
    uint8_t to_file = SQUARE_TO_FILE(MOVE_TO(move));
    uint8_t to_rank = SQUARE_TO_RANK(MOVE_TO(move));
    
    // Basic move notation (e.g. "e2e4")
    str[0] = 'a' + from_file;
    str[1] = '1' + from_rank;
    str[2] = 'a' + to_file;
    str[3] = '1' + to_rank;
    
    // Add promotion piece if applicable
    if (MOVE_IS_PROMOTION(move)) {
        switch (MOVE_PROMOTION(move)) {
            case PIECE_KNIGHT: str[4] = 'n'; break;
            case PIECE_BISHOP: str[4] = 'b'; break;
            case PIECE_ROOK:   str[4] = 'r'; break;
            case PIECE_QUEEN:  str[4] = 'q'; break;
            default:           str[4] = '?'; break;
        }
        str[5] = '\0';
    } else {
        str[4] = '\0';
    }
    
    return str;
}

Move move_from_string(const char* str) {
    if (!str || strlen(str) < 4) return 0;
    
    // Parse squares
    uint8_t from_file = tolower(str[0]) - 'a';
    uint8_t from_rank = str[1] - '1';
    uint8_t to_file = tolower(str[2]) - 'a';
    uint8_t to_rank = str[3] - '1';
    
    // Validate squares
    if (from_file >= BOARD_WIDTH_8x8 || from_rank >= BOARD_HEIGHT_8x8 ||
        to_file >= BOARD_WIDTH_8x8 || to_rank >= BOARD_HEIGHT_8x8) return 0;
    
    uint8_t from_square = COORD_TO_SQUARE(from_file, from_rank);
    uint8_t to_square = COORD_TO_SQUARE(to_file, to_rank);
    
    // Parse flags
    uint32_t flags = MOVE_FLAG_QUIET;
    
    if (str[4]) {
        flags = MOVE_FLAG_PROMOTION;
        switch (tolower(str[4])) {
            case 'n': flags |= MOVE_PROMOTE_KNIGHT; break;
            case 'b': flags |= MOVE_PROMOTE_BISHOP; break;
            case 'r': flags |= MOVE_PROMOTE_ROOK; break;
            case 'q': flags |= MOVE_PROMOTE_QUEEN; break;
            default: return 0; // Invalid promotion piece
        }
        
        // Check if it's a valid promotion square (rank 1 or 8)
        if (to_rank != 0 && to_rank != 7) return 0;
    }
    
    return MOVE_MAKE(from_square, to_square, flags);
}

// Validate a move structure
bool move_is_valid(Move move) {
    // Extract squares
    uint8_t from = MOVE_FROM(move);
    uint8_t to = MOVE_TO(move);
    
    // First check if source square is in range (0-127) and valid on 0x88 board
    if (from >= BOARD_SIZE_0x88 || INVALID_SQUARE(from)) {
        return false;
    }
    
    // Then check target square
    if (to >= BOARD_SIZE_0x88 || INVALID_SQUARE(to)) {
        return false;
    }
    
    // Can't move to same square
    if (from == to) {
        return false;
    }
    
    // Check promotion if applicable
    if (MOVE_IS_PROMOTION(move)) {
        uint8_t promo = MOVE_PROMOTION(move);
        if (promo < PIECE_KNIGHT || promo > PIECE_QUEEN) {
            return false;
        }
        
        // Must promote to rank 1 or 8
        uint8_t to_rank = SQUARE_TO_RANK(to);
        if (to_rank != 0 && to_rank != 7) {
            return false;
        }
    }
    
    return true;
}