#include "board.h"

#include <stdio.h>
#include <string.h> // strcpy

// Initial position piece placement
static const uint8_t initial_position[64] = {
    MAKE_PIECE(COLOR_WHITE, PIECE_ROOK),   MAKE_PIECE(COLOR_WHITE, PIECE_KNIGHT),
    MAKE_PIECE(COLOR_WHITE, PIECE_BISHOP), MAKE_PIECE(COLOR_WHITE, PIECE_QUEEN),
    MAKE_PIECE(COLOR_WHITE, PIECE_KING),   MAKE_PIECE(COLOR_WHITE, PIECE_BISHOP),
    MAKE_PIECE(COLOR_WHITE, PIECE_KNIGHT), MAKE_PIECE(COLOR_WHITE, PIECE_ROOK),
    
    MAKE_PIECE(COLOR_WHITE, PIECE_PAWN),   MAKE_PIECE(COLOR_WHITE, PIECE_PAWN),
    MAKE_PIECE(COLOR_WHITE, PIECE_PAWN),   MAKE_PIECE(COLOR_WHITE, PIECE_PAWN),
    MAKE_PIECE(COLOR_WHITE, PIECE_PAWN),   MAKE_PIECE(COLOR_WHITE, PIECE_PAWN),
    MAKE_PIECE(COLOR_WHITE, PIECE_PAWN),   MAKE_PIECE(COLOR_WHITE, PIECE_PAWN),
    
    0, 0, 0, 0, 0, 0, 0, 0,  // Empty squares
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    
    MAKE_PIECE(COLOR_BLACK, PIECE_PAWN),   MAKE_PIECE(COLOR_BLACK, PIECE_PAWN),
    MAKE_PIECE(COLOR_BLACK, PIECE_PAWN),   MAKE_PIECE(COLOR_BLACK, PIECE_PAWN),
    MAKE_PIECE(COLOR_BLACK, PIECE_PAWN),   MAKE_PIECE(COLOR_BLACK, PIECE_PAWN),
    MAKE_PIECE(COLOR_BLACK, PIECE_PAWN),   MAKE_PIECE(COLOR_BLACK, PIECE_PAWN),
    
    MAKE_PIECE(COLOR_BLACK, PIECE_ROOK),   MAKE_PIECE(COLOR_BLACK, PIECE_KNIGHT),
    MAKE_PIECE(COLOR_BLACK, PIECE_BISHOP), MAKE_PIECE(COLOR_BLACK, PIECE_QUEEN),
    MAKE_PIECE(COLOR_BLACK, PIECE_KING),   MAKE_PIECE(COLOR_BLACK, PIECE_BISHOP),
    MAKE_PIECE(COLOR_BLACK, PIECE_KNIGHT), MAKE_PIECE(COLOR_BLACK, PIECE_ROOK)
};

void board_init(Board *board) {
    board_clear(board);
    board->side_to_move = COLOR_WHITE;
}

void board_clear(Board *board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        board->squares[i] = PIECE_NONE;
    }
    board->king_square[0] = board->king_square[1] = 0;
}

void board_reset(Board *board) {
    board_clear(board);
    
    // Place pieces from initial position
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            int square = coord_to_square(file, rank);
            uint8_t piece = initial_position[rank * 8 + file];
            board_set_piece(board, square, piece);
            
            // Track king positions
            if (GET_PIECE_TYPE(piece) == PIECE_KING) {
                board->king_square[GET_PIECE_COLOR(piece) == COLOR_WHITE ? 0 : 1] = square;
            }
        }
    }
    
    board->side_to_move = COLOR_WHITE;
}

int coord_to_square(int file, int rank) {
    return rank * 16 + file;
}

void square_to_coord(int square, int *file, int *rank) {
    *file = square & 7;
    *rank = square >> 4;
}

bool is_valid_square(int square) {
    return !INVALID_SQUARE(square);
}

void board_set_piece(Board *board, int square, uint8_t piece) {
    if (is_valid_square(square)) {
        board->squares[square] = piece;
        
        // Update king position if placing/removing a king
        if (GET_PIECE_TYPE(piece) == PIECE_KING) {
            board->king_square[GET_PIECE_COLOR(piece) == COLOR_WHITE ? 0 : 1] = square;
        }
    }
}

uint8_t board_get_piece(const Board *board, int square) {
    return is_valid_square(square) ? board->squares[square] : PIECE_NONE;
}

bool board_is_empty(const Board *board, int square) {
    return board_get_piece(board, square) == PIECE_NONE;
}

const char *piece_to_char(uint8_t piece) {
    static const char *piece_chars[] = {
        ".", "P", "N", "B", "R", "Q", "K",
        ".", "p", "n", "b", "r", "q", "k"
    };
    
    int index = GET_PIECE_TYPE(piece);
    if (GET_PIECE_COLOR(piece) == COLOR_BLACK) {
        index += 7;
    }
    return piece_chars[index];
}

// Convert FEN piece char to our piece encoding
static uint8_t char_to_piece(char c) {
    uint8_t piece = PIECE_NONE;
    uint8_t color = (c >= 'a' && c <= 'z') ? COLOR_BLACK : COLOR_WHITE;
    
    // Convert to uppercase for unified handling
    c = (c >= 'a' && c <= 'z') ? c - 32 : c;
    
    switch(c) {
        case 'P': piece = PIECE_PAWN; break;
        case 'N': piece = PIECE_KNIGHT; break;
        case 'B': piece = PIECE_BISHOP; break;
        case 'R': piece = PIECE_ROOK; break;
        case 'Q': piece = PIECE_QUEEN; break;
        case 'K': piece = PIECE_KING; break;
    }
    
    return piece ? MAKE_PIECE(color, piece) : PIECE_NONE;
}

bool board_set_fen(Board *board, const char *fen) {
    if (!fen) return false;
    
    board_clear(board);
    
    int rank = 7;  // Start from the 8th rank (FEN starts from rank 8)
    int file = 0;
    
    // Parse piece placement
    while (*fen && *fen != ' ') {
        if (*fen == '/') {
            if (file != 8) return false;  // Incomplete rank
            rank--;
            file = 0;
        }
        else if (*fen >= '1' && *fen <= '8') {
            file += *fen - '0';
        }
        else {
            if (file >= 8 || rank < 0) return false;  // Invalid position
            uint8_t piece = char_to_piece(*fen);
            if (piece == PIECE_NONE && *fen != ' ') return false;  // Invalid piece
            
            int square = coord_to_square(file, rank);
            board_set_piece(board, square, piece);
            file++;
        }
        fen++;
    }
    
    if (!*fen || rank != 0 || file != 8) return false;
    
    // Parse side to move
    fen++;  // Skip space
    if (*fen == 'w') board->side_to_move = COLOR_WHITE;
    else if (*fen == 'b') board->side_to_move = COLOR_BLACK;
    else return false;
    
    // For now, we'll ignore castling rights, en passant, and move counts
    // We'll add those when implementing the relevant features
    
    return true;
}

void board_get_fen(const Board *board, char *fen, size_t len) {
    if (!fen || len < 24) return;  // Minimum FEN length for piece placement
    
    char *ptr = fen;
    int empty;
    
    // Piece placement
    for (int rank = 7; rank >= 0; rank--) {
        empty = 0;
        for (int file = 0; file < 8; file++) {
            uint8_t piece = board_get_piece(board, coord_to_square(file, rank));
            if (piece == PIECE_NONE) {
                empty++;
            } else {
                if (empty) {
                    *ptr++ = '0' + empty;
                    empty = 0;
                }
                *ptr++ = *piece_to_char(piece);
            }
        }
        if (empty) {
            *ptr++ = '0' + empty;
        }
        if (rank > 0) {
            *ptr++ = '/';
        }
    }
    
    // Side to move
    *ptr++ = ' ';
    *ptr++ = board->side_to_move == COLOR_WHITE ? 'w' : 'b';
    
    // For now, use minimal values for other fields
    strcpy(ptr, " - - 0 1");
}

void board_display(const Board *board) {
    printf("\n  a b c d e f g h\n");
    printf(" ─────────────────\n");
    
    for (int rank = 7; rank >= 0; rank--) {
        printf("%d│", rank + 1);
        for (int file = 0; file < 8; file++) {
            int square = coord_to_square(file, rank);
            printf("%s ", piece_to_char(board_get_piece(board, square)));
        }
        printf("│%d\n", rank + 1);
    }
    
    printf(" ─────────────────\n");
    printf("  a b c d e f g h\n\n");
    
    printf("Side to move: %s\n", board->side_to_move == COLOR_WHITE ? "White" : "Black");
}