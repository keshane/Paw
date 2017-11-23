#include <cstdint>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>

void DIE(char *message);

/**
 * Utility struct to pack rank and file into one type
 */
typedef struct {
    int8_t file;
    int8_t rank;
} Coordinate;

/**
 * Defines the different type of pieces
 */
enum class PieceType {
    None = 0,
    Pawn = 1,
    Rook = 2,
    Knight = 3,
    Bishop = 4,
    Queen = 5,
    King = 6,
};

/**
 * Defines the color of a component of the game
 */
enum class Color {
    None,
    Black,
    White
};

/**
 * Defines a specific piece by its type and color
 */
typedef struct {
    PieceType piece_type;
    Color color;
} Piece;

inline bool operator== (Piece a, Piece b)
{
    if (a.piece_type == b.piece_type && a.color == b.color)
    {
        return true;
    }
    else
    {
        return false;
    }
}



namespace std
{
    template<>
    struct hash<PieceType>
    {
        std::size_t operator() (const PieceType& p) const
        {
            return (std::hash<int>()(static_cast<int>(p)));
        }
    };
    template<>
    struct hash<Color>
    {
        std::size_t operator() (const Color& c) const
        {
            return (std::hash<int>()(static_cast<int>(c)));
        }
    };
    template<>
    struct hash<Piece>
    {
        std::size_t operator() (const Piece& p) const
        {
            return (std::hash<PieceType>()(p.piece_type) ^ std::hash<Color>()(p.color));
        }
    };
}

/**
 * Represents a square on the chessboard.
 */
typedef struct {
    bool occupied;
    Piece piece;
} Square;

/**
 * Defines the non-exclusive categories of moves that can be made.
 */
enum class MoveType : uint8_t {
    Normal = 1,
    Capture = 1 << 1,
    En_Passant = 1 << 2,
    Queenside_Castle = 1 << 3,
    Kingside_Castle = 1 << 4,
    Check = 1 << 5,
    Checkmate = 1 << 6,

};

inline MoveType operator& (MoveType a, MoveType b)  {
     return static_cast<MoveType>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inline MoveType operator| (MoveType a, MoveType b)  {
     return static_cast<MoveType>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

/**
 * Represents a single chess move.
 */
typedef struct Move {
    Coordinate source;
    Coordinate destination;

    Piece piece;
    MoveType move_type = MoveType::Normal;

} Move;

/**
 * Represents the physical chessboard with pieces.
 */
class Board {
public:
    Board();
    bool move(Coordinate source, Coordinate destination);
    bool place_piece(Piece* piece, Coordinate destination);
    bool remove_piece_from(Coordinate source);
    Coordinate get_location_of(Piece* piece);
    Square get_piece(Coordinate source); 
    void print_board();
private:
    Square _board[8][8];
    std::unordered_map<Piece, std::string> piece_to_unicode = 
    {
        {Piece{PieceType::King, Color::White}, std::string("\u2654")},
        {Piece{PieceType::Queen, Color::White}, std::string("\u2655")},
        {Piece{PieceType::Rook, Color::White}, std::string("\u2656")},
        {Piece{PieceType::Bishop, Color::White}, std::string("\u2657")},
        {Piece{PieceType::Knight, Color::White}, std::string("\u2658")},
        {Piece{PieceType::Pawn, Color::White}, std::string("\u2659")},

        {Piece{PieceType::King, Color::Black}, std::string("\u265A")},
        {Piece{PieceType::Queen, Color::Black}, std::string("\u265B")},
        {Piece{PieceType::Rook, Color::Black}, std::string("\u265C")},
        {Piece{PieceType::Bishop, Color::Black}, std::string("\u265D")},
        {Piece{PieceType::Knight, Color::Black}, std::string("\u265E")},
        {Piece{PieceType::Pawn, Color::Black}, std::string("\u265F")},
    };
};



/**
 * This class contains functions to parse algebraic notation in string form
 * into a Move type
 */
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
    Parser();
    Move parse_algebraic_notation(std::string notation);

};


/**
 * Represents a player to make the moves on the chessboard.
 */
class Player {
public:
    void make_move(std::string move);
    Player(std::string name, Board& chessboard, Color color);

private:
    Board _chessboard;
    Parser _move_parser;
    std::string _name;
    Color _color;
    bool make_pawn_move(Move pawn_move);
    bool make_bishop_move(Move bishop_move);
    bool make_knight_move(Move knight_move);
    bool make_rook_move(Move rook_move);
    bool make_queen_move(Move queen_move);
    bool make_king_move(Move king_move);
    bool make_castle_move(Move castle_move);

    Move fill_move(Move partial_move);

    bool verify_move(Move move);
    void make_valid_move(Move move);

    // TODO change signature
    bool is_valid_move(PieceType moving_piece, Coordinate source, Coordinate destination);
    bool is_valid_pawn_move(Coordinate source, Coordinate destination);
    bool is_valid_rook_move(Coordinate source, Coordinate destination);
    bool is_valid_knight_move(Coordinate source, Coordinate destination);
    bool is_valid_bishop_move(Coordinate source, Coordinate destination);
    bool is_valid_queen_move(Coordinate source, Coordinate destination);
    bool is_valid_king_move(Coordinate source, Coordinate destination);

    bool is_valid_rook_slide(Coordinate source, Coordinate destination);
    bool is_valid_bishop_slide(Coordinate source, Coordinate destination);
    bool is_valid_queen_slide(Coordinate source, Coordinate destination);

    bool is_valid_capture(Coordinate source, Coordinate destination);
    bool is_valid_pawn_capture(Coordinate source, Coordinate destination);
    bool is_valid_rook_capture(Coordinate source, Coordinate destination);
    bool is_valid_knight_capture(Coordinate source, Coordinate destination);
    bool is_valid_bishop_capture(Coordinate source, Coordinate destination);
    bool is_valid_queen_capture(Coordinate source, Coordinate destination);
    bool is_valid_king_capture(Coordinate source, Coordinate destination);

    bool is_clear_path(Coordinate source, Coordinate destination);


    std::vector<Coordinate> get_source_squares(Coordinate source, PieceType piece_type);
    int8_t _en_passant_rank;
    int8_t _direction;

};

/**
 * This contains the overall game with all the other components
 */
class Game {
public:
    Game(std::string white_name, std::string black_name);
    bool enter_move(std::string);
    void print_board();

private:
    Board _chessboard;
    Player _black_player;
    Player _white_player;
    bool _white_move;
    std::vector<Piece> black_pieces;
    std::vector<Piece> white_pieces;
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
