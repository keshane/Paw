/**
 * Takes input in FEN
 *
 * I am reinventing the wheel for exercise.
 */
#include <cstdint>
#include <iostream>
#include <locale>

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
        parse_normal_move(move);
    }
    else {
        parse_special_move(move);
    }
}


/** TODO: scrap this and make it a FSM
 */
Move Board::parse_normal_move(std::string move) {
    Move parsed_move;
    int i = 1;
    char& c = move.at(move.length() - i);
    parsed_move.to_i = c - '1';

    i++;
    c = move.at(move.length() - i);

    if (c >= 'a' && c <= 'h') {
        parsed_move.to_j = c - 'a';
    }
    else {
        throw std::invalid_argument("invalid notation");
    }

    i++;
    c = move.at(move.length() - i);

    if (c == 'x') {
        i++;
        c = move.at(move.length() - i);
        parsed_move.capture = true;
    }
    else {
        parsed_move.capture = false;
    }

    if (i > move.length && !parsed_move.capture) {
        verify_pawn_move(parsed_move);
    }
    else if (i > move.length && parsed_move.capture) {
        throw std::invalid_argument("invalid notation");
    }

    if (c >= 'a' && c <= 'h' &&
        i == move.length() && parsed_move.capture) {
        verify_pawn_capture(parsed_move);
    }
    else if (i == move.length() && c == 'R') {
       verify_rook_move(parsed_move);
    }
    else if (i == move.length() && c == 'N') {
       verify_knight_move(parsed_move);
    }
    else if (i == move.length() && c == 'B') {
       verify_bishop_move(parsed_move);
    }
    else if (i == move.length() && c == 'Q') {
       verify_queen_move(parsed_move);
    }
    else if (i == move.length() && c == 'K') {
       verify_king_move(parsed_move);
    }
    else if (i != move.length() && c >= 'a' && c <= 'h') {}




    



    

}


    



void DIE(char const *message) {
    std::cout << message << std::endl;
}

int main(int argc, char *argv[]) {
    Board board;
    board.print_board();
}




