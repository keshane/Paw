#include <vector>
#include <cstdint>
#include <string>

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
    BLACK_KING = 12,
    NUMBER_OF_PIECES = 13
};

typedef struct Move {
    int8_t from_i = -1;
    int8_t from_j = -1;

    int8_t to_i;
    int8_t to_j;

    union {
        char piece_name;
        Piece piece;
    };
    bool capture;
} Move;

typedef struct Coordinate {
    int8_t i;
    int8_t j;
} Coordinate;

void print_move(Move move);
class Board {
    private:
        uint8_t board[8][8];
        bool white_move;
        Move parse_normal_move(std::string move);
        Move parse_special_move(std::string move);
        Move verify_normal_move(Move move);
        void execute_normal_move(Move move);
        bool has_clear_horiz(int8_t row, int8_t ja, int8_t jb);
        bool has_clear_vert(int8_t col, int8_t ia, int8_t ib);
        bool has_clear_diag(int8_t ia, int8_t ja, int8_t ib, int8_t jb);
        Move verify_rook_move(Move move);
        Move verify_bishop_move(Move move);
        Move verify_knight_move(Move move);
        Move verify_queen_move(Move move);
        Move verify_king_move(Move move);
        Move verify_pawn_move(Move move);

        std::vector<Coordinate> piece_locations[NUMBER_OF_PIECES];
        bool dummy;
        bool dummy2;

    public:
        Board();
        void print_board();
        bool enter_move(std::string move);
};
