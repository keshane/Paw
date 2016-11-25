/**
 * Takes input in FEN
 *
 * I am reinventing the wheel for exercise.
 */
#include <cstdint>
#include <iostream>
#include <locale>
#include <stdexcept>

void DIE(char *message);

enum Piece : uint8_t {
    WHITE_PAWN = 1,
    WHITE_ROOK = 2,
    WHITE_KNIGHT = 3,
    WHITE_BISHOP = 4,
    WHITE_QUEEN = 5,
    WHITE_KING = 6,
    BLACK_PAWN = 7,
    BLACK_ROOK = 8,
    BLACK_KNIGHT = 9,
    BLACK_BISHOP = 10,
    BLACK_QUEEN = 11,
    BLACK_KING = 12
};

typedef struct Move {
    int from_i;
    int from_j;

    int to_i;
    int to_j;

    // these two last for alignment purposes
    // but I guess I could also make the above
    // uint8_t instead of ints? TODO
    char piece;
    bool capture;
} Move;

 
class Board {
    private:
        uint8_t board[8][8];
        bool white_move;
    public:
        Board();
        void print_board();
        bool enter_move(std::string move);
        Move parse_normal_move(std::string move);
        Move parse_special_move(std::string move);
};

Board::Board() {
    board[0][0] = WHITE_ROOK;
    board[0][7] = WHITE_ROOK;
    board[0][1] = WHITE_KNIGHT;
    board[0][6] = WHITE_KNIGHT;
    board[0][2] = WHITE_BISHOP;
    board[0][5] = WHITE_BISHOP;
    board[0][3] = WHITE_QUEEN;
    board[0][4] = WHITE_KING;

    for (int i = 0; i < 8; i++) {
        board[1][i] = WHITE_PAWN;
    }

    board[7][0] = BLACK_ROOK;
    board[7][7] = BLACK_ROOK;
    board[7][1] = BLACK_KNIGHT;
    board[7][6] = BLACK_KNIGHT;
    board[7][2] = BLACK_BISHOP;
    board[7][5] = BLACK_BISHOP;
    board[7][3] = BLACK_QUEEN;
    board[7][4] = BLACK_KING;

    for (int i = 0; i < 8; i++) {
        board[6][i] = BLACK_PAWN;
    }

    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = 0;
        }
    }
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
}


bool Board::enter_move(std::string move) {
    if (move.back() >= '1' && move.back() <= '8') {
        try {
            parse_normal_move(move);
        }
        catch (std::invalid_argument& e) {
            std::cout << e.what() << std::endl;
        }

    }
    else {
        parse_special_move(move);
    }
}

Move Board::parse_special_move(std::string move) {
    Move parsed_move;
    return parsed_move;
}

Move Board::parse_normal_move(std::string move) {
    Move parsed_move;

    int state;
    const int to_file = 1, to_rank = 2, from_file = 3, capture = 4, from_rank = 5, piece = 6;

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
                parsed_move.to_i = *it - '0';

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
                 * 'capture' state is necessary to make sure
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
                parsed_move.from_i = *it - '0';

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
                else {
                    throw std::invalid_argument("invalid notation");
                }
                break;

            case piece:
                parsed_move.piece = *it;

                it++;
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
   // board.parse_normal_move("NFxe4");
    board.enter_move("NFxe4");
}




