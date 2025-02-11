#include "board.h"

#include <stdio.h>

static uint8_t char_to_piece(char c);
static bool fen_parse_piece_placement(Board *board, const char **fen);
static bool fen_parse_side_to_move(Board *board, const char **fen);
static bool fen_parse_castling_rights(Board *board, const char **fen);
static bool fen_parse_en_passant(Board *board, const char **fen);
static bool fen_parse_halfmove_clock(Board *board, const char **fen);
static bool fen_parse_fullmove_number(Board *board, const char **fen);

void board_init(Board *board) {
    board_clear(board);
    board->side_to_move = COLOR_WHITE;
}

void board_clear(Board *board) {
    for (uint8_t i = 0; i < BOARD_SIZE_0x88; ++i) {
        board->squares[i] = PIECE_NONE;
    }
    board->castling_rights = 0;
}

void board_reset(Board *board) {
    board_clear(board);

    // Place pieces from initial position
    static const char *initial_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    board_set_fen(board, initial_fen);

    static const uint8_t e1_square = COORD_TO_SQUARE(4, 0);
    static const uint8_t e7_square = COORD_TO_SQUARE(4, 7);

    board->king_square[0] = e1_square;
    board->king_square[1] = e7_square;
    
    board->side_to_move         = COLOR_WHITE;
    board->castling_rights      = CASTLING_WHITE_KINGSIDE | CASTLING_WHITE_QUEENSIDE
                                | CASTLING_BLACK_KINGSIDE | CASTLING_BLACK_QUEENSIDE;
    board->en_passant_square    = NO_SQUARE;
    board->halfmove_clock       = 0;
    board->fullmove_number      = 1;
}

void square_to_coord(uint8_t square, uint8_t *file, uint8_t *rank) {
    *file = SQUARE_TO_FILE(square);
    *rank = SQUARE_TO_RANK(square);
}

bool is_valid_square(uint8_t square) {
    return !INVALID_SQUARE(square);
}

void board_set_piece(Board *board, uint8_t square, uint8_t piece) {
    if (!is_valid_square(square)) return;
    
    board->squares[square] = piece;
        
    // Update king position if placing/removing a king
    if (IS_PIECE_TYPE(piece,  PIECE_KING)) {
        board->king_square[IS_PIECE_COLOR(piece, COLOR_WHITE) ? 0 : 1] = square;
    }
}

uint8_t board_get_piece(const Board *board, uint8_t square) {
    return is_valid_square(square) ? board->squares[square] : PIECE_NONE;
}

bool board_is_empty(const Board *board, uint8_t square) {
    return board_get_piece(board, square) == PIECE_NONE;
}

void board_set_castling_rights(Board *board, uint8_t rights) {
    board->castling_rights = rights;
}

uint8_t board_get_castling_rights(const Board *board) {
    return board->castling_rights;
}

void board_set_en_passant_square(Board *board, uint8_t square) {
    board->en_passant_square = square;
}

int8_t board_get_en_passant_square(const Board *board) {
    return board->en_passant_square;
}

bool board_set_fen(Board *board, const char *fen) {
    if (!fen) return false;
    board_clear(board);
    
    if (!fen_parse_piece_placement(board, &fen)) return false;
    if (!fen_parse_side_to_move(board, &fen)) return false;
    if (!fen_parse_castling_rights(board, &fen)) return false;
    if (!fen_parse_en_passant(board, &fen)) return false;
    if (!fen_parse_halfmove_clock(board, &fen)) return false;
    if (!fen_parse_fullmove_number(board, &fen)) return false;

    return true;
}

void board_get_fen(const Board *board, char *fen, uint8_t len) {
    if (!fen || len < FEN_MIN_LENGTH) return;
    
    char *ptr = fen;
    uint8_t empty = 0;
    
    // Piece placement
    for (int8_t rank = BOARD_HEIGHT_8x8 - 1; rank >= 0; --rank) {
        empty = 0;
        for (uint8_t file = 0; file < BOARD_WIDTH_8x8; ++file) {
            uint8_t piece = board_get_piece(board, COORD_TO_SQUARE(file, rank));
            
            if (piece == PIECE_NONE) {
                empty++;
                continue;
            }
            
            if (empty) {
                *ptr++ = '0' + empty;
                empty = 0;
            }
            *ptr++ = PIECE_TO_CHAR(piece);
        }
        
        if (empty) *ptr++ = '0' + empty;
        if (rank > 0) *ptr++ = '/';
    }
    
    // Side to move
    *ptr++ = ' ';
    *ptr++ = board->side_to_move == COLOR_WHITE ? 'w' : 'b';
    
    // Castling rights
    *ptr++ = ' ';
    if (board->castling_rights == 0) {
        *ptr++ = '-';
    } else {
        if (board->castling_rights & CASTLING_WHITE_KINGSIDE) *ptr++ = 'K';
        if (board->castling_rights & CASTLING_WHITE_QUEENSIDE) *ptr++ = 'Q';
        if (board->castling_rights & CASTLING_BLACK_KINGSIDE) *ptr++ = 'k';
        if (board->castling_rights & CASTLING_BLACK_QUEENSIDE) *ptr++ = 'q';
    }
    
    // En passant square
    *ptr++ = ' ';
    if (board->en_passant_square == NO_SQUARE) {
        *ptr++ = '-';
    } else {
        *ptr++ = 'a' + SQUARE_TO_FILE(board->en_passant_square);
        *ptr++ = '1' + SQUARE_TO_RANK(board->en_passant_square);
    }
    
    // Halfmove clock and fullmove number
    sprintf(ptr, " %d %d", board->halfmove_clock, board->fullmove_number);
}

void board_display(const Board *board) {
    printf("\n  a b c d e f g h\n");
    printf(" ─────────────────\n");

    // must be strings due to multi-byte encoding :(
    static const char *UNICODE_PIECES[] = {                 
        ".", "♟", "♞", "♝", "♜", "♛", "♚",
        ".", "♙", "♘", "♗", "♖", "♕", "♔"
    };
    
    for (int8_t rank = BOARD_HEIGHT_8x8 - 1; rank >= 0; --rank) {
        printf("%d│", rank + 1);
        for (uint8_t file = 0; file < BOARD_WIDTH_8x8; ++file) {
            uint8_t square = COORD_TO_SQUARE(file, rank);
            printf("%s ", UNICODE_PIECES[GET_PIECE_DISPLAY_INDEX(board_get_piece(board, square))]);
        }
        printf("│%d\n", rank + 1);
    }
    
    printf(" ─────────────────\n");
    printf("  a b c d e f g h\n\n");
    
    printf("Side to move: %s\n", board->side_to_move == COLOR_WHITE ? "White" : "Black");
}

static uint8_t char_to_piece(char c) {
    uint8_t piece = PIECE_NONE;
    uint8_t color = (c >= 'a' && c <= 'z') ? COLOR_BLACK : COLOR_WHITE;
    
    // Convert to uppercase for unified handling
    c = (c >= 'a' && c <= 'z') ? c - ASCII_UPPER_OFFSET : c;
    
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

static bool fen_parse_piece_placement(Board *board, const char **fen) {
    uint8_t file = 0;
    int8_t rank = 7;
    
    while (**fen && **fen != ' ') {
        if (**fen == '/') {
            if (file != BOARD_WIDTH_8x8) return false;
            rank--;
            file = 0;
            (*fen)++;
            continue;
        }
        
        if (**fen >= '1' && **fen <= '0' + BOARD_WIDTH_8x8) {
            file += **fen - '0';
            (*fen)++;
            continue;
        }
        
        if (file >= BOARD_WIDTH_8x8 || rank < 0) return false;
        
        uint8_t piece = char_to_piece(**fen);
        if (piece == PIECE_NONE && **fen != ' ') return false;
        
        board_set_piece(board, COORD_TO_SQUARE(file, rank), piece);
        file++;
        (*fen)++;
    }
    
    return (**fen && rank == 0 && file == 8);
}

static bool fen_parse_side_to_move(Board *board, const char **fen) {
    if (!*++(*fen)) return false;  // Skip space and check
    if (**fen == 'w') board->side_to_move = COLOR_WHITE;
    else if (**fen == 'b') board->side_to_move = COLOR_BLACK;
    else return false;
    
    return true;
}

static bool fen_parse_castling_rights(Board *board, const char **fen) {
    if (!*++(*fen) || **fen != ' ') return false;  // Skip color and check space
    if (!*++(*fen)) return false;  // Skip space and check
    
    if (**fen != '-') {
        while (**fen && **fen != ' ') {
            switch (**fen) {
                case 'K': board->castling_rights |= CASTLING_WHITE_KINGSIDE; break;
                case 'Q': board->castling_rights |= CASTLING_WHITE_QUEENSIDE; break;
                case 'k': board->castling_rights |= CASTLING_BLACK_KINGSIDE; break;
                case 'q': board->castling_rights |= CASTLING_BLACK_QUEENSIDE; break;
                default: return false;
            }
            (*fen)++;
        }
    } else (*fen)++;
    
    return (**fen && **fen == ' ');
}

static bool fen_parse_en_passant(Board *board, const char **fen) {
    if (!*++(*fen)) return false;  // Skip space and check
    
    if (**fen != '-') {
        if (!(*fen)[0] || !(*fen)[1]) return false;
        
        int8_t file = (*fen)[0] - 'a';
        int8_t rank = (*fen)[1] - '1';
        if (file < 0 || file > BOARD_WIDTH_8x8 - 1 || rank < 0 || rank > BOARD_HEIGHT_8x8 - 1) return false;
        
        board->en_passant_square = COORD_TO_SQUARE(file, rank);
        *fen += 2;
    } else {
        board->en_passant_square = NO_SQUARE;
        (*fen)++;
    }
    
    return (**fen && **fen == ' ');
}

static bool fen_parse_halfmove_clock(Board *board, const char **fen) {
    if (!*++(*fen)) return false;  // Skip space and check
    if (sscanf(*fen, "%hu", &board->halfmove_clock) != 1) return false;
    
    while (**fen && **fen != ' ') (*fen)++;
    return **fen;
}

static bool fen_parse_fullmove_number(Board *board, const char **fen) {
    if (!*++(*fen)) return false;  // Skip space and check
    if (sscanf(*fen, "%hu", &board->fullmove_number) != 1) return false;
    
    return true;
}
