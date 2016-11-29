/**
 *
 */
#include <cstdint>
#include <iostream>
#include <locale>
#include <stdexcept>
#include <string>
#include <vector>
#include "chess_gui.h"

void DIE(char *message);

 


Board::Board() {
    // Fill in white pieces
    board[0][0] = WHITE_ROOK;
    board[0][7] = WHITE_ROOK;
    board[0][1] = WHITE_KNIGHT;
    board[0][6] = WHITE_KNIGHT;
    board[0][2] = WHITE_BISHOP;
    board[0][5] = WHITE_BISHOP;
    board[0][3] = WHITE_QUEEN;
    board[0][4] = WHITE_KING;

    piece_locations[WHITE_ROOK].push_back({0,0});
    piece_locations[WHITE_ROOK].push_back({0,7});
    piece_locations[WHITE_KNIGHT].push_back({0,1});
    piece_locations[WHITE_KNIGHT].push_back({0,6});
    piece_locations[WHITE_BISHOP].push_back({0,2});
    piece_locations[WHITE_BISHOP].push_back({0,5});
    piece_locations[WHITE_QUEEN].push_back({0,3});
    piece_locations[WHITE_KING].push_back({0,4});

    for (int8_t i = 0; i < 8; i++) {
        board[1][i] = WHITE_PAWN;
        piece_locations[WHITE_PAWN].push_back({1,i});
    }

    // Fill in black pieces
    board[7][0] = BLACK_ROOK;
    board[7][7] = BLACK_ROOK;
    board[7][1] = BLACK_KNIGHT;
    board[7][6] = BLACK_KNIGHT;
    board[7][2] = BLACK_BISHOP;
    board[7][5] = BLACK_BISHOP;
    board[7][3] = BLACK_QUEEN;
    board[7][4] = BLACK_KING;

    piece_locations[BLACK_ROOK].push_back({7,0});
    piece_locations[BLACK_ROOK].push_back({7,7});
    piece_locations[BLACK_KNIGHT].push_back({7,1});
    piece_locations[BLACK_KNIGHT].push_back({7,6});
    piece_locations[BLACK_BISHOP].push_back({7,2});
    piece_locations[BLACK_BISHOP].push_back({7,5});
    piece_locations[BLACK_QUEEN].push_back({7,3});
    piece_locations[BLACK_KING].push_back({7,4});
    for (int8_t i = 0; i < 8; i++) {
        board[6][i] = BLACK_PAWN;
        piece_locations[BLACK_PAWN].push_back({6,i});
    }

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }

    white_move = true;
}

void Board::print_board() {
    std::cout << "              BLACK\n";
    // top of board
    std::cout << "\u250C";
    for (int k = 0; k < 7; k++) {
        std::cout << "\u2500\u2500\u2500\u252C";
    }
    std::cout << "\u2500\u2500\u2500\u2510\n";


    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            switch (board[i][j]) {
                case BLACK_PAWN:
                    std::cout << "\u2502 \u265F ";
                    break;
                case BLACK_KNIGHT:
                    std::cout << "\u2502 \u265E ";
                    break;
                case BLACK_BISHOP:
                    std::cout << "\u2502 \u265D ";
                    break;
                case BLACK_ROOK:
                    std::cout << "\u2502 \u265C ";
                    break;
                case BLACK_QUEEN:
                    std::cout << "\u2502 \u265B ";
                    break;
                case BLACK_KING:
                    std::cout << "\u2502 \u265A ";
                    break;
                case WHITE_PAWN:
                    std::cout << "\u2502 \u2659 ";
                    break;
                case WHITE_KNIGHT:
                    std::cout << "\u2502 \u2658 ";
                    break;
                case WHITE_BISHOP:
                    std::cout << "\u2502 \u2657 ";
                    break;
                case WHITE_ROOK:
                    std::cout << "\u2502 \u2656 ";
                    break;
                case WHITE_QUEEN:
                    std::cout << "\u2502 \u2655 ";
                    break;
                case WHITE_KING:
                    std::cout << "\u2502 \u2654 ";
                    break;
                default:
                    std::cout << "\u2502   ";
                    break;
            }
        }
        
        // right bar
        std::cout << "\u2502\n";

        if (i > 0) { 
            // row boundary
            std::cout << "\u251C";
            for (int k = 0; k < 7; k++) {
                std::cout << "\u2500\u2500\u2500\u253C";
            }
            std::cout << "\u2500\u2500\u2500\u2524\n";
        }
    }

    // print bottom of board
    std::cout << "\u2514";
    for (int k = 0; k < 7; k++) {
        std::cout << "\u2500\u2500\u2500\u2534";
    }
    std::cout << "\u2500\u2500\u2500\u2518\n";

    std::cout << "              WHITE\n";

    if (white_move) {
        std::cout << "WHITE TO MOVE\n";
    }
    else {
        std::cout << "BLACK TO MOVE\n";
    }
}


bool Board::enter_move(std::string move) {
    Move parsed_move;
    if (move.back() >= '1' && move.back() <= '8') {
        try {
            parsed_move = parse_normal_move(move);
        }
        catch (std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }

    }
    else {
        parse_special_move(move);
    }

    // TODO: verify move
    // complete_move = verify_normal_move(parsed_move);

    if (white_move) {
        switch (parsed_move.piece_name) {
            case 'P':
                parsed_move.piece = WHITE_PAWN;
                break;
            case 'R':
                parsed_move.piece = WHITE_ROOK;
                break;
            case 'N':
                parsed_move.piece = WHITE_KNIGHT;
                break;
            case 'B':
                parsed_move.piece = WHITE_BISHOP;
                break;
            case 'Q':
                parsed_move.piece = WHITE_QUEEN;
                break;
            case 'K':
                parsed_move.piece = WHITE_KING;
                break;
        }
    }
    else {
        switch (parsed_move.piece_name) {
            case 'P':
                parsed_move.piece = BLACK_PAWN;
                break;
            case 'R':
                parsed_move.piece = BLACK_ROOK;
                break;
            case 'N':
                parsed_move.piece = BLACK_KNIGHT;
                break;
            case 'B':
                parsed_move.piece = BLACK_BISHOP;
                break;
            case 'Q':
                parsed_move.piece = BLACK_QUEEN;
                break;
            case 'K':
                parsed_move.piece = BLACK_KING;
                break;
        }
    }
    execute_normal_move(parsed_move);

    white_move = !white_move;
    return true;
}

void Board::execute_normal_move(Move move) {
    board[move.to_i][move.to_j] = board[move.from_i][move.from_j];
    board[move.from_i][move.from_j] = 0;
}

Move Board::parse_special_move(std::string move) {
    Move parsed_move;
    return parsed_move;
}

/**
 * Check if there are any pieces between board[row][ja] and board[row][jb]
 *
 * @param row the row index
 * @param ja the column index of the first square
 * @param jb the column index of the second square
 *
 * @return true if there are no blockers between the squares, false otherwise
 */
bool Board::has_clear_horiz(int8_t row, int8_t ja, int8_t jb) {
    // We don't allow pieces to not move
    if (ja == jb) {
        return false;
    }
    for (int8_t j = std::min(ja, jb) + 1; j < std::max(ja, jb); j++) {
        if (board[row][j] > 0) {
            return false;
        }
    }
    return true;
}

/**
 * Check if there are any pieces between board[ia][col] and board[ib][col]
 *
 * @param col the column index
 * @param ia the row index of the first square
 * @param ib the row index of the second square
 *
 * @return true if there are no blockers between the squares, false otherwise
 */
bool Board::has_clear_vert(int8_t col, int8_t ia, int8_t ib) {
    // We don't allow pieces to move to their current square 
    if (ia == ib) {
        return false;
    }
    for (int8_t i = std::min(ia, ib) + 1; i < std::max(ia, ib); i++) {
        if (board[i][col] > 0) {
            return false;
        }
    }
    return true;
}

/**
 * Check if there are any pieces between board[ia][ja] and board[ib][jb]
 *
 * @param ia the row index of the first square
 * @param ja the col index of the first square
 * @param ib the row index of the second square
 * @param jb the col index of the second square
 *
 * @return true if there are no blockers between the squares, false otherwise
 */
bool Board::has_clear_diag(int8_t ia, int8_t ja, int8_t ib, int8_t jb) {
    if (ia == ib && ja == jb)
        return false;
    int8_t incr_i = (ib - ia) / std::abs(ib - ia);
    int8_t incr_j = (jb - ja) / std::abs(jb - ja);
    for (int i = ia + incr_i, j = ja + incr_j;
         i != ib && j != jb;
         i += incr_i, j += incr_j) {
        if (board[i][j] > 0) {
            return false;
        }
    }
    return true;
}

         

Move Board::verify_bishop_move(Move move) {
    std::vector<Coordinate>::iterator it = piece_locations[move.piece].begin();
    bool verified = false;
    // no from_square specified
    if (move.from_i < 0 && move.from_j < 0) {
        for (; it != piece_locations[move.piece].end(); it++) {
            if (std::abs((*it).i - move.to_i) == std::abs((*it).j - move.to_j)) {
                bool is_clear = has_clear_diag((*it).i, (*it).j, move.to_i, move.to_j);

                // Checks to see if there was another piece that could have made this move
                if (is_clear && verified) {
                    throw std::invalid_argument("Imprecise notation - placeholder exception");
                }

                if (is_clear) {
                    move.from_i = (*it).i;
                    move.from_j = (*it).j;

                    verified = true;
                }
            }
        }
    }
    // rank specified
    else if (move.from_i >= 0 && move.from_j < 0) {
        for (; it != piece_locations[move.piece].end(); it++) {
            if ((*it).i == move.from_i &&
                std::abs((*it).i - move.to_i) == std::abs((*it).j - move.to_j)) {
                bool is_clear = has_clear_diag((*it).i, (*it).j, move.to_i, move.to_j);

                // Checks to see if there was another piece that could have made this move
                if (is_clear && verified) {
                    throw std::invalid_argument("Imprecise notation - placeholder exception");
                }

                if (is_clear) {
                    move.from_i = (*it).i;
                    move.from_j = (*it).j;

                    verified = true;
                }
            }
        }
    }
    // file specified
    else if (move.from_i < 0 && move.from_j >= 0) {
        for (; it != piece_locations[move.piece].end(); it++) {
            if ((*it).j == move.from_j &&
                std::abs((*it).i - move.to_i) == std::abs((*it).j - move.to_j)) {
                bool is_clear = has_clear_diag((*it).i, (*it).j, move.to_i, move.to_j);

                // Checks to see if there was another piece that could have made this move
                if (is_clear && verified) {
                    throw std::invalid_argument("Imprecise notation - placeholder exception");
                }

                if (is_clear) {
                    move.from_i = (*it).i;
                    move.from_j = (*it).j;

                    verified = true;
                }
            }
        }
    }
    else { // both move.from_i and move.from_j were specified
        for (; it != piece_locations[move.piece].end(); it++) {
            if ((*it).i == move.from_i &&
                (*it).j == move.from_j && 
                std::abs((*it).i - move.to_i) == std::abs((*it).j - move.to_j)) {
                bool is_clear = has_clear_diag((*it).i, (*it).j, move.to_i, move.to_j);

                // Checks to see if there was another piece that could have made this move
                if (is_clear && verified) {
                    throw std::invalid_argument("Imprecise notation - placeholder exception");
                }

                if (is_clear) {
                    move.from_i = (*it).i;
                    move.from_j = (*it).j;

                    verified = true;
                }
            }
        }
    }

    if (!verified) {
        throw std::invalid_argument("invalid move - placeholder exception");
    }

    return move;
}

Move Board::verify_rook_move(Move move) {
    std::vector<Coordinate>::iterator it = piece_locations[move.piece].begin();
    bool verified = false;
    // if 'from' square isn't specified
    if (move.from_i < 0 && move.from_j < 0) {
        // We need to check all pieces in case the notation is imprecise
        for (; it != piece_locations[move.piece].end(); it++) {
            // if the rook is on the same rank as the 'to' square...
            if ((*it).i == move.to_i) {
                bool is_clear = has_clear_horiz((*it).i, (*it).j, move.to_j);

                if (is_clear && verified) {
                    throw std::invalid_argument("Imprecise notation - placeholder exception");
                }

                if (is_clear) {
                    move.from_i = (*it).i;
                    move.from_j = (*it).j;

                    verified = true;
                }
            }
            else if ((*it).j == move.to_j) {
                bool is_clear = has_clear_vert((*it).j, (*it).i, move.to_i);

                if (is_clear && verified) {
                    throw std::invalid_argument("Imprecise notation - placeholder exception");
                }

                if (is_clear) {
                    move.from_i = (*it).i;
                    move.from_j = (*it).j;

                    verified = true;
                }
            }

        }
        if (!verified) {
            throw std::invalid_argument("Invalid move");
        }
    }
    else if (move.from_i >= 0 && move.from_j < 0) {
        for (; it != piece_locations[move.piece].end(); it++) {
            if ((*it).i == move.from_i) {
                bool is_clear = has_clear_horiz((*it).i, (*it).j, move.to_j);

                if (is_clear && verified) {
                    throw std::invalid_argument("Imprecise notation - placeholder exception");
                }

                if (is_clear) {
                    move.from_i = (*it).i;
                    move.from_j = (*it).j;

                    verified = true;
                }
            }
        }
        if (!verified) {
            throw std::invalid_argument("Invalid move");
        }
    }
    else if (move.from_i < 0 && move.from_j >= 0) {
        for (; it != piece_locations[move.piece].end(); it++) {
            if ((*it).j == move.from_j) {
                bool is_clear = has_clear_vert((*it).j, (*it).i, move.to_i);

                if (is_clear && verified) {
                    throw std::invalid_argument("Imprecise notation - placeholder exception");
                }

                if (is_clear) {
                    move.from_i = (*it).i;
                    move.from_j = (*it).j;

                    verified = true;
                }
            }
        }
        if (!verified) {
            throw std::invalid_argument("Invalid move");
        }
    }
    else { // both move.from_i and move.from_j were specified
        for (; it != piece_locations[move.piece].end(); it++) {
            if ((*it).i == move.from_i && (*it).j == move.from_j) {
                bool is_clear;
                if (move.from_i == move.to_i) {
                    is_clear = has_clear_horiz(move.from_i, move.from_j, move.to_j);
                }
                else if (move.from_j == move.to_j) {
                    is_clear = has_clear_vert(move.from_j, move.from_i, move.to_i);
                }
                else {
                    is_clear = false;
                }


                if (is_clear && verified) {
                    throw std::invalid_argument("Imprecise notation - placeholder exception");
                }

                if (is_clear) {
                    move.from_i = (*it).i;
                    move.from_j = (*it).j;

                    verified = true;
                }
            }
        }
    }

    if (!verified) {
        throw std::invalid_argument("Invalid move");
    }

    return move;
}
 
Move Board::verify_normal_move(Move move) {
    Move verified_move;
    switch (move.piece) {
        case WHITE_ROOK:
        case BLACK_ROOK:
            verified_move = verify_rook_move(move);
            break;

        case WHITE_BISHOP:
        case BLACK_BISHOP:
            verified_move = verify_bishop_move(move);
            break;
            
        default:
            break;
    }

    return move;
}



/**
 * Emulates a finite state machine to parse the input string
 * of algebraic notation from the end to the beginning
 *
 * @param move a string of the form
 *             [RNBQK]?[a-h]?[1-8]?x?[a-h][1-8]
 *
 * @return a Move with the appropriate variables filled out
 */
Move Board::parse_normal_move(std::string move) {
    Move parsed_move;

    int state;
    const int to_file = 1, to_rank = 2, capture = 3, from_file = 4, from_rank = 5, piece = 6;

    std::string::const_reverse_iterator it = move.crbegin();

    state = 0;
    while (it != move.crend()) {
        switch (state) {
            case 0: 
                if (*it >= '1' && *it <= '8') {
                    state = to_rank;
                }
                else {
                    throw std::invalid_argument("invalid notation");
                }
                break;

            case to_rank:
                parsed_move.to_i = *it - '1';

                it++;
                if (*it >= 'a' && *it <= 'h') {
                    state = to_file;
                }
                else {
                    throw std::invalid_argument("invalid notation");
                }
                break;

            case to_file:
                parsed_move.to_j = *it - 'a';

                it++;
                /**
                 * Needing to set
                 * parsed_move.capture = [true | false] virtually 
                 * doubles the number of following states, but
                 * practically we can just have parsed_move.capture
                 * differentiate between otherwise identical states
                 */
                if (*it == 'x') {
                    parsed_move.capture = true;
                    state = capture;
                }
                else if (*it >= '1' && *it <= '8') {
                    parsed_move.capture = false;
                    state = from_rank;
                }
                else if (*it >= 'a' && *it <= 'h') {
                    parsed_move.capture = false;
                    state = from_file;
                }
                else if (*it == 'R' || *it == 'N' ||
                         *it == 'B' || *it == 'Q' ||
                         *it == 'K') {
                    parsed_move.capture = false;
                    state = piece;
                }
                else {
                    throw std::invalid_argument("invalid notation");
                }
 
                break;

            case capture:
                /** 
                 * This case is essentially a repeat of the
                 * else-if statements in case to_file. This
                 * 'capture' case is necessary to make sure
                 * we haven't reached the beginning of the string
                 * yet.
                 */
                it++;
                if (*it >= '1' && *it <= '8') {
                    state = from_rank;
                }
                else if (*it >= 'a' && *it <= 'h') {
                    state = from_file;
                }
                else if (*it == 'R' || *it == 'N' ||
                         *it == 'B' || *it == 'Q' ||
                         *it == 'K') {
                    state = piece;
                }
                else {
                    throw std::invalid_argument("invalid notation");
                }
                break;

            case from_rank:
                parsed_move.from_i = *it - '1';

                it++;
                if (*it >= 'a' && *it <= 'h') {
                    state = from_file;
                }
                else if (*it == 'R' || *it == 'N' ||
                         *it == 'B' || *it == 'Q' ||
                         *it == 'K') {
                    state = piece;
                }
                else {
                    throw std::invalid_argument("invalid notation");
                }
                break;

            case from_file:
                parsed_move.from_j = *it - 'a';

                it++;
                if (*it == 'R' || *it == 'N' ||
                    *it == 'B' || *it == 'Q' ||
                    *it == 'K') {
                    state = piece;
                }
                else if (it == move.crend()) {
                    parsed_move.piece_name = 'P';
                }
                else {
                    throw std::invalid_argument("invalid notation");
                }
                break;

            case piece:
                parsed_move.piece_name = *it;

                it++;

                state = 100;
                break;

            default:
                throw std::invalid_argument("unknown state when parsing");
                break;
        }
    }

    return parsed_move;
}


    



void DIE(char const *message) {
    std::cout << message << std::endl;
}

int main(int argc, char *argv[]) {
    Board board;
    board.print_board();
    std::string move;
    while(getline(std::cin, move)) {
        if (move.empty() || move == "\n")
            continue;
        if (move == "exit")
            break;
        board.enter_move(move);
        board.print_board();
    }
    std::cout << "Thank you for playing today\n";
}




