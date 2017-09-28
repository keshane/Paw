#include <vector>
#include <cstdint>
#include <string>
#include <stack>

void DIE(char *message);

typedef struct {
    int8_t rank;
    int8_t file;
    Coordinate(int8_t file, int8_t rank) : this->file(file)), this->rank(rank));
} Coordinate;

enum class PieceType : uint8_t {
    None = 0,
    Pawn = 1,
    Rook = 2,
    Knight = 3,
    Bishop = 4,
    Queen = 5,
    King = 6,
};

enum class Color : uint8_t {
    Black,
    White,
    None
};

typedef struct {
    PieceType piece_type;
    Color color;
    Piece(PieceType p, Color c);
} Piece;


enum class MoveType : uint8_t {
    Normal = 1,
    Capture = 1 << 1,
    En_Passant = 1 << 2,
    Queenside_Castle = 1 << 3,
    Kingside_Castle = 1 << 4,
    Check = 1 << 5,
    Checkmate = 1 << 6,

};

MoveType operator& (MoveType a, MoveType b)  {
     return static_cast<MoveType>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

MoveType operator| (MoveType a, MoveType b)  {
     return static_cast<MoveType>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

class Board {
public:
    Board();
    bool move(Coordinate source, Coordinate destination);
    void print_board();
private:
    Piece board[8][8];
};

typedef struct Move {
    Coordinate source;
    Coordinate destination;

    Piece piece;
    MoveType move_type = MoveType::Normal;

} Move;

class Parser {
private:
    std::string move_notation;
    Move parsed_move;
    void parse_normal_move();
    void parse_destination_rank();
    void parse_destination_file();
    void parse_capture();
    void parse_moving_piece();
    void parse_source_rank();
    void parse_source_file();
public:
    Move parse_algebraic_notation(std::string notation);

};


class Player {
public:
    void make_move(std::string move);
    Player(std::string name, Board* chessboard, Color color);

private:
    Board* chessboard;
    Parser move_parser;
    std::string name;
    bool make_pawn_move(Move pawn_move);
    bool make_bishop_move(Move bishop_move);
    bool make_knight_move(Move knight_move);
    bool make_rook_move(Move rook_move);
    bool make_queen_move(Move queen_move);
    bool make_king_move(Move king_move);
    bool make_castle_move(Move castle_move);

    std::vector<Coordinate> get_source_squares(Coordinate source, PieceType piece_type);

};

class Game {
public:
    Game(std::string white_name, std::string black_name);
    bool enter_move(std::string);
    void print_board();

private:
    Board chessboard;
    Player black_player;
    Player white_player;
    // TODO move history


};



//typedef struct Square {
//    Piece piece;
//    Coordinate coordinate;
//} Square;
//
//void print_move(Move move);
//class Board {
//    private:
//        uint8_t board[8][8];
//        bool white_move;
//        Move parse_normal_move(std::string move);
//        Move parse_special_move(std::string move);
//        Move verify_normal_move(Move move);
//        void execute_normal_move(Move move);
//        bool has_clear_horiz(int8_t row, int8_t ja, int8_t jb);
//        bool has_clear_vert(int8_t col, int8_t ia, int8_t ib);
//        bool has_clear_diag(int8_t ia, int8_t ja, int8_t ib, int8_t jb);
//        Move verify_rook_move(Move move);
//        Move verify_bishop_move(Move move);
//        Move verify_knight_move(Move move);
//        Move verify_queen_move(Move move);
//        Move verify_king_move(Move move);
//        Move verify_pawn_move(Move move);
//
//        std::vector<Coordinate> piece_locations[NUMBER_OF_PIECES];
//        std::stack<Square> captured_pieces;
//        bool dummy;
//        bool dummy2;
//        Coordinate en_passant;
//        bool en_passant_possible;
//
//        bool king_in_check(Piece king);
//
//    public:
//        Board();
//        void print_board();
//        bool enter_move(std::string move);
//};
//
//class Piece {
//    public:
//        virtual Coordinate get_location();
//        virtual void set_location();
//        virtual std::vector<Coordinate> get_possible_moves();
//};
//
//
//class Pawn : public Piece {
//    private:
//        Coordinate _location;
//
//    public:
//        Coordinate get_location();
//        void set_location();
//        std::vector<Coordinate> get_possible_moves();
//};
//
//class Bishop : public Piece {
//    private:
//        Coordinate _location;
//        std::vector<Coordinates> calculate_possible_moves();
//        std::vector<Coordinates> _possible_moves();
//
//    public:
//        Coordinate get_location();
//        void set_location();
//        std::vector<Coordinate> get_possible_moves();
//};
//
//class Knight : public Piece {
//    private:
//        Coordinate _location;
//
//    public:
//        Coordinate get_location();
//        void set_location();
//        std::vector<Coordinate> get_possible_moves();
//};
//
//class Rook : public Piece {
//    private:
//        Coordinate _location;
//
//    public:
//        Coordinate get_location();
//        void set_location();
//        std::vector<Coordinate> get_possible_moves();
//};
//
//class Queen : public Piece {
//    private:
//        Coordinate _location;
//
//    public:
//        Coordinate get_location();
//        void set_location();
//        std::vector<Coordinate> get_possible_moves();
//};
//
//class King : public Piece {
//    private:
//        Coordinate _location;
//
//    public:
//        Coordinate get_location();
//        void set_location();
//        std::vector<Coordinate> get_possible_moves();
//};
