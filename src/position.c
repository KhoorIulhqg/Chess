#include "position.h"
#include <string.h> // memset()

#include "zobrist.h"

void position_init(Position *pos) {
    if (!pos) return;
    position_clear(pos);
    board_init(&pos->board);
}

void position_reset(Position *pos) {
    if (!pos) return;
    position_clear(pos);
    board_reset(&pos->board);
    
    // Initialize first position state
    pos->state_history[0].position_key = position_generate_key(pos);
    pos->state_history[0].castling_rights = pos->board.castling_rights;
    pos->state_history[0].en_passant_square = pos->board.en_passant_square;
    pos->state_history[0].halfmove_clock = 0;
    pos->state_history[0].captured_piece = PIECE_NONE;
    
    pos->history_count = 1;
}

void position_clear(Position *pos) {
    if (!pos) return;
    memset(pos, 0, sizeof(Position));
}

uint32_t position_generate_key(const Position *pos) {
    if (!pos) return 0;
    
    uint32_t key = 0;
    
    // Hash pieces
    for (uint8_t sq = 0; sq < BOARD_SIZE_8x8; sq++) {
        uint8_t piece = board_get_piece(&pos->board, sq);
        if (piece != PIECE_NONE) {
            uint8_t color = GET_PIECE_COLOR(piece) == COLOR_WHITE ? 0 : 1;
            uint8_t type = GET_PIECE_TYPE(piece);
            key ^= ZOBRIST_PIECES[color][type][sq];
        }
    }
    
    // Hash castling rights
    key ^= ZOBRIST_CASTLING[pos->board.castling_rights & 0xF];
    
    // Hash en passant
    if (pos->board.en_passant_square != NO_SQUARE) {
        uint8_t file = SQUARE_TO_FILE(pos->board.en_passant_square);
        key ^= ZOBRIST_EN_PASSANT[file];
    }
    
    // Hash side to move
    if (pos->board.side_to_move == COLOR_BLACK) {
        key ^= ZOBRIST_SIDE_TO_MOVE;
    }
    
    return key;
}

bool position_is_valid(const Position *pos) {
    if (!pos) return false;
    
    // Check basic structure validity
    if (pos->ply >= MAX_PLY) return false;
    if (pos->history_count > pos->ply + 1) return false;
    if (pos->history_count == 0) return false;
    
    // Verify current hash matches computed hash
    uint32_t computed_key = position_generate_key(pos);
    if (computed_key != pos->state_history[pos->history_count - 1].position_key) {
        return false;
    }

    // Verify exactly one king per side
    int white_kings = 0;
    int black_kings = 0;
    bool white_king_found = false;
    bool black_king_found = false;
    uint8_t white_king_square = pos->board.king_square[0];
    uint8_t black_king_square = pos->board.king_square[1];

    for (uint8_t sq = 0; sq < BOARD_SIZE_0x88; sq++) {
        if (INVALID_SQUARE(sq)) continue;
        uint8_t piece = board_get_piece(&pos->board, sq);
        if (piece == PIECE_NONE) continue;

        if (IS_PIECE_TYPE(piece, PIECE_KING)) {
            if (IS_PIECE_COLOR(piece, COLOR_WHITE)) {
                white_kings++;
                if (sq == white_king_square) white_king_found = true;
            } else {
                black_kings++;
                if (sq == black_king_square) black_king_found = true;
            }
        }
    }
    if (white_kings != 1 || black_kings != 1 || !white_king_found || !black_king_found) return false;

    // Verify en passant square validity
    int8_t ep_sq = pos->state_history[pos->history_count - 1].en_passant_square;
    if (ep_sq != NO_SQUARE) {
        uint8_t rank = SQUARE_TO_RANK(ep_sq);
        // En passant square must be on rank 3 for White or rank 6 for Black
        if (pos->board.side_to_move == COLOR_WHITE && rank != 5) return false;
        if (pos->board.side_to_move == COLOR_BLACK && rank != 2) return false;
    }

    // Verify castling rights consistency
    uint8_t castling = pos->state_history[pos->history_count - 1].castling_rights;
    if (castling & CASTLING_WHITE_KINGSIDE) {
        // Verify white king and kingside rook in original positions
        if (board_get_piece(&pos->board, COORD_TO_SQUARE(4, 0)) != MAKE_PIECE(COLOR_WHITE, PIECE_KING) ||
            board_get_piece(&pos->board, COORD_TO_SQUARE(7, 0)) != MAKE_PIECE(COLOR_WHITE, PIECE_ROOK)) {
            return false;
        }
    }
    if (castling & CASTLING_WHITE_QUEENSIDE) {
        // Verify white king and queenside rook
        if (board_get_piece(&pos->board, COORD_TO_SQUARE(4, 0)) != MAKE_PIECE(COLOR_WHITE, PIECE_KING) ||
            board_get_piece(&pos->board, COORD_TO_SQUARE(0, 0)) != MAKE_PIECE(COLOR_WHITE, PIECE_ROOK)) {
            return false;
        }
    }
    if (castling & CASTLING_BLACK_KINGSIDE) {
        // Verify black king and kingside rook
        if (board_get_piece(&pos->board, COORD_TO_SQUARE(4, 7)) != MAKE_PIECE(COLOR_BLACK, PIECE_KING) ||
            board_get_piece(&pos->board, COORD_TO_SQUARE(7, 7)) != MAKE_PIECE(COLOR_BLACK, PIECE_ROOK)) {
            return false;
        }
    }
    if (castling & CASTLING_BLACK_QUEENSIDE) {
        // Verify black king and queenside rook
        if (board_get_piece(&pos->board, COORD_TO_SQUARE(4, 7)) != MAKE_PIECE(COLOR_BLACK, PIECE_KING) ||
            board_get_piece(&pos->board, COORD_TO_SQUARE(0, 7)) != MAKE_PIECE(COLOR_BLACK, PIECE_ROOK)) {
            return false;
        }
    }

    // Verify no pawns on first or last ranks
    for (uint8_t file = 0; file < BOARD_WIDTH_8x8; file++) {
        uint8_t piece_rank_1 = board_get_piece(&pos->board, COORD_TO_SQUARE(file, 0));
        uint8_t piece_rank_8 = board_get_piece(&pos->board, COORD_TO_SQUARE(file, 7));
        if (IS_PIECE_TYPE(piece_rank_1, PIECE_PAWN) || IS_PIECE_TYPE(piece_rank_8, PIECE_PAWN)) {
            return false;
        }
    }

    return true;
}

bool position_compare(const Position *pos1, const Position *pos2) {
    if (!pos1 || !pos2) return false;
    
    // Quick hash comparison first
    if (pos1->state_history[pos1->history_count - 1].position_key !=
        pos2->state_history[pos2->history_count - 1].position_key) {
        return false;
    }
    
    // Compare board states
    for (uint8_t sq = 0; sq < BOARD_SIZE_8x8; sq++) {
        if (board_get_piece(&pos1->board, sq) != board_get_piece(&pos2->board, sq)) {
            return false;
        }
    }
    
    // Compare current state
    const PositionState *state1 = &pos1->state_history[pos1->history_count - 1];
    const PositionState *state2 = &pos2->state_history[pos2->history_count - 1];
    
    return (pos1->board.side_to_move == pos2->board.side_to_move &&
            state1->castling_rights == state2->castling_rights &&
            state1->en_passant_square == state2->en_passant_square &&
            state1->halfmove_clock == state2->halfmove_clock);
}