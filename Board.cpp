#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>
#include "chess_gui.h"

Board::Board()
{
    for (int file = 0; file < 8; file++)
    {
        for (int rank = 0; rank < 8; rank++)
        {
            _board[file][rank] = Square{false, Piece{PieceType::None, Color::None}};
        }
    }
    _board[0][0] = Square{true, Piece{PieceType::Rook, Color::White}};
    _board[1][0] = Square{true, Piece{PieceType::Knight, Color::White}};
    _board[2][0] = Square{true, Piece{PieceType::Bishop, Color::White}};
    _board[3][0] = Square{true, Piece{PieceType::Queen, Color::White}};
    _board[4][0] = Square{true, Piece{PieceType::King, Color::White}};
    _board[5][0] = Square{true, Piece{PieceType::Bishop, Color::White}};
    _board[6][0] = Square{true, Piece{PieceType::Knight, Color::White}};
    _board[7][0] = Square{true, Piece{PieceType::Rook, Color::White}};

    _board[0][1] = Square{true, Piece{PieceType::Pawn, Color::White}};
    _board[1][1] = Square{true, Piece{PieceType::Pawn, Color::White}};
    _board[2][1] = Square{true, Piece{PieceType::Pawn, Color::White}};
    _board[3][1] = Square{true, Piece{PieceType::Pawn, Color::White}};
    _board[4][1] = Square{true, Piece{PieceType::Pawn, Color::White}};
    _board[5][1] = Square{true, Piece{PieceType::Pawn, Color::White}};
    _board[6][1] = Square{true, Piece{PieceType::Pawn, Color::White}};
    _board[7][1] = Square{true, Piece{PieceType::Pawn, Color::White}};

    _board[0][7] = Square{true, Piece{PieceType::Rook, Color::Black}};
    _board[1][7] = Square{true, Piece{PieceType::Knight, Color::Black}};
    _board[2][7] = Square{true, Piece{PieceType::Bishop, Color::Black}};
    _board[3][7] = Square{true, Piece{PieceType::Queen, Color::Black}};
    _board[4][7] = Square{true, Piece{PieceType::King, Color::Black}};
    _board[5][7] = Square{true, Piece{PieceType::Bishop, Color::Black}};
    _board[6][7] = Square{true, Piece{PieceType::Knight, Color::Black}};
    _board[7][7] = Square{true, Piece{PieceType::Rook, Color::Black}};

    _board[0][6] = Square{true, Piece{PieceType::Pawn, Color::Black}};
    _board[1][6] = Square{true, Piece{PieceType::Pawn, Color::Black}};
    _board[2][6] = Square{true, Piece{PieceType::Pawn, Color::Black}};
    _board[3][6] = Square{true, Piece{PieceType::Pawn, Color::Black}};
    _board[4][6] = Square{true, Piece{PieceType::Pawn, Color::Black}};
    _board[5][6] = Square{true, Piece{PieceType::Pawn, Color::Black}};
    _board[6][6] = Square{true, Piece{PieceType::Pawn, Color::Black}};
    _board[7][6] = Square{true, Piece{PieceType::Pawn, Color::Black}};
}
bool Board::move(Coordinate source, Coordinate destination) {
    Square source_square = get_piece(source);

    if (source_square.occupied) {
        // TODO save history
        _board[source.file][source.rank].occupied = false;
        _board[source.file][source.rank].piece.piece_type = PieceType::None;
        _board[source.file][source.rank].piece.color = Color::None;
        _board[destination.file][destination.rank] = Square{true, source_square.piece};
        print_board();
        DEBUG("happy path");
        DEBUG(std::string("source occupied: " + std::to_string(_board[source.file][source.rank].occupied)));
        return true;
    }
    else {
        return false;
    }
}

Square Board::get_piece(Coordinate square) {
    if (square.file >= 0 && square.file < 8 && square.rank >= 0 && square.rank < 8) {
        return _board[square.file][square.rank];
    }
    else
    {
        // TODO throw
        throw std::logic_error("TODO board out of bounds");
    }
}

void Board::print_board()
{
    // TOP OF BOARD
    std::cout << "\u250C";
    for (int file = 0; file < 7; file++) {
        std::cout << "\u2500\u2500\u2500\u252C";
    }
    std::cout << "\u2500\u2500\u2500\u2510\n";


    for (int rank = 7; rank >= 0; rank--)
    {
        for (int file = 0; file <= 7; file++)
        {
            std::cout << "\u2502 "; // vertical line
            Square square = get_piece(Coordinate{file, rank});
            if (square.occupied)
            {
                std::cout << piece_to_unicode[square.piece];
            }
            else
            {
                std::cout << " ";
            }
            std::cout << " ";
        }

        // right bar
        std::cout << "\u2502\n";

        if (rank > 0)
        {
            // row boundary
            std::cout << "\u251C";
            for (int file = 0; file < 7; file++) {
                std::cout << "\u2500\u2500\u2500\u253C";
            }
            std::cout << "\u2500\u2500\u2500\u2524\n";

        }
    }
    // print bottom of board
    std::cout << "\u2514";
    for (int file = 0; file < 7; file++) {
        std::cout << "\u2500\u2500\u2500\u2534";
    }
    std::cout << "\u2500\u2500\u2500\u2518\n";

}
// /**
//  *
//  */
// #include <cstdint>
// #include <iostream>
// #include <locale>
// #include <stdexcept>
// #include <string>
// #include <vector>
// #include <algorithm>
// #include <stack>
// #include "chess_gui.h"

// Board::Board() {
//     // Fill in white pieces
//     board[0][0] = WHITE_ROOK;
//     board[0][7] = WHITE_ROOK;
//     board[0][1] = WHITE_KNIGHT;
//     board[0][6] = WHITE_KNIGHT;
//     board[0][2] = WHITE_BISHOP;
//     board[0][5] = WHITE_BISHOP;
//     board[0][3] = WHITE_QUEEN;
//     board[0][4] = WHITE_KING;

//     piece_locations[WHITE_ROOK].push_back({0,0});
//     piece_locations[WHITE_ROOK].push_back({0,7});
//     piece_locations[WHITE_KNIGHT].push_back({0,1});
//     piece_locations[WHITE_KNIGHT].push_back({0,6});
//     piece_locations[WHITE_BISHOP].push_back({0,2});
//     piece_locations[WHITE_BISHOP].push_back({0,5});
//     piece_locations[WHITE_QUEEN].push_back({0,3});
//     piece_locations[WHITE_KING].push_back({0,4});

//     for (int8_t i = 0; i < 8; i++) {
//         board[1][i] = WHITE_PAWN;
//         piece_locations[WHITE_PAWN].push_back({1,i});
//     }

//     // Fill in black pieces
//     board[7][0] = BLACK_ROOK;
//     board[7][7] = BLACK_ROOK;
//     board[7][1] = BLACK_KNIGHT;
//     board[7][6] = BLACK_KNIGHT;
//     board[7][2] = BLACK_BISHOP;
//     board[7][5] = BLACK_BISHOP;
//     board[7][3] = BLACK_QUEEN;
//     board[7][4] = BLACK_KING;

//     piece_locations[BLACK_ROOK].push_back({7,0});
//     piece_locations[BLACK_ROOK].push_back({7,7});
//     piece_locations[BLACK_KNIGHT].push_back({7,1});
//     piece_locations[BLACK_KNIGHT].push_back({7,6});
//     piece_locations[BLACK_BISHOP].push_back({7,2});
//     piece_locations[BLACK_BISHOP].push_back({7,5});
//     piece_locations[BLACK_QUEEN].push_back({7,3});
//     piece_locations[BLACK_KING].push_back({7,4});
//     for (int8_t i = 0; i < 8; i++) {
//         board[6][i] = BLACK_PAWN;
//         piece_locations[BLACK_PAWN].push_back({6,i});
//     }

//     for (int i = 2; i < 6; i++) {
//         for (int j = 0; j < 8; j++) {
//             board[i][j] = 0;
//         }
//     }

//     white_move = true;

// }

// /**
//  * Prints the current state of the board
//  */
// void Board::print_board() {
//     std::cout << "              BLACK\n";
//     // top of board
//     std::cout << "\u250C";
//     for (int k = 0; k < 7; k++) {
//         std::cout << "\u2500\u2500\u2500\u252C";
//     }
//     std::cout << "\u2500\u2500\u2500\u2510\n";


//     for (int i = 7; i >= 0; i--) {
//         for (int j = 0; j < 8; j++) {
//             switch (board[i][j]) {
//                 case BLACK_PAWN:
//                     std::cout << "\u2502 \u265F ";
//                     break;
//                 case BLACK_KNIGHT:
//                     std::cout << "\u2502 \u265E ";
//                     break;
//                 case BLACK_BISHOP:
//                     std::cout << "\u2502 \u265D ";
//                     break;
//                 case BLACK_ROOK:
//                     std::cout << "\u2502 \u265C ";
//                     break;
//                 case BLACK_QUEEN:
//                     std::cout << "\u2502 \u265B ";
//                     break;
//                 case BLACK_KING:
//                     std::cout << "\u2502 \u265A ";
//                     break;
//                 case WHITE_PAWN:
//                     std::cout << "\u2502 \u2659 ";
//                     break;
//                 case WHITE_KNIGHT:
//                     std::cout << "\u2502 \u2658 ";
//                     break;
//                 case WHITE_BISHOP:
//                     std::cout << "\u2502 \u2657 ";
//                     break;
//                 case WHITE_ROOK:
//                     std::cout << "\u2502 \u2656 ";
//                     break;
//                 case WHITE_QUEEN:
//                     std::cout << "\u2502 \u2655 ";
//                     break;
//                 case WHITE_KING:
//                     std::cout << "\u2502 \u2654 ";
//                     break;
//                 default:
//                     std::cout << "\u2502   ";
//                     break;
//             }
//         }
        
//         // right bar
//         std::cout << "\u2502\n";

//         if (i > 0) { 
//             // row boundary
//             std::cout << "\u251C";
//             for (int k = 0; k < 7; k++) {
//                 std::cout << "\u2500\u2500\u2500\u253C";
//             }
//             std::cout << "\u2500\u2500\u2500\u2524\n";
//         }
//     }

//     // print bottom of board
//     std::cout << "\u2514";
//     for (int k = 0; k < 7; k++) {
//         std::cout << "\u2500\u2500\u2500\u2534";
//     }
//     std::cout << "\u2500\u2500\u2500\u2518\n";

//     std::cout << "              WHITE\n";

//     if (white_move) {
//         std::cout << "WHITE TO MOVE\n";
//     }
//     else {
//         std::cout << "BLACK TO MOVE\n";
//     }
// }


// /**
//  * Accepts a move in algebraic notation as a string and attempts
//  * to make that move
//  *
//  * @param move algebraic notation for a move on the chess board
//  *
//  * @return true if the notation and move are valid and the move
//  *         is made, false otherwise
//  */
// bool Board::enter_move(std::string move) {
//     Move parsed_move;
//     if (move.back() >= '1' && move.back() <= '8') {
//         try {
//             parsed_move = parse_normal_move(move);
//         }
//         catch (std::invalid_argument& e) {
//             std::cout << e.what() << std::endl;
//             return false;
//         }

//     }
//     else {
//         parse_special_move(move);
//     }

//     if (white_move) {
//         switch (parsed_move.piece_name) {
//             case 'P':
//                 parsed_move.piece = WHITE_PAWN;
//                 break;
//             case 'R':
//                 parsed_move.piece = WHITE_ROOK;
//                 break;
//             case 'N':
//                 parsed_move.piece = WHITE_KNIGHT;
//                 break;
//             case 'B':
//                 parsed_move.piece = WHITE_BISHOP;
//                 break;
//             case 'Q':
//                 parsed_move.piece = WHITE_QUEEN;
//                 break;
//             case 'K':
//                 parsed_move.piece = WHITE_KING;
//                 break;
//         }
//     }
//     else {
//         switch (parsed_move.piece_name) {
//             case 'P':
//                 parsed_move.piece = BLACK_PAWN;
//                 break;
//             case 'R':
//                 parsed_move.piece = BLACK_ROOK;
//                 break;
//             case 'N':
//                 parsed_move.piece = BLACK_KNIGHT;
//                 break;
//             case 'B':
//                 parsed_move.piece = BLACK_BISHOP;
//                 break;
//             case 'Q':
//                 parsed_move.piece = BLACK_QUEEN;
//                 break;
//             case 'K':
//                 parsed_move.piece = BLACK_KING;
//                 break;
//         }
//     }

//     parsed_move.pre_en_passant = false; // default
//     parsed_move.en_passant = false; // default

//     Move verified_move;
//     try {
//         verified_move = verify_normal_move(parsed_move);
//     }
//     catch (std::invalid_argument &e) {
//         std::cout << e.what() << std::endl;
//         return false;
//     }

//     print_move(parsed_move);
//     print_move(verified_move);
//     // TODO: Check for check and checkmate
//     execute_normal_move(verified_move);



//     white_move = !white_move;
//     return true;
// }

// void print_move(Move move) {
//     std::cout << "From i: " + std::to_string(move.from_i) << std::endl;
//     std::cout << "From j: " + std::to_string(move.from_j) << std::endl;
//     std::cout << "To i: " + std::to_string(move.to_i) << std::endl;
//     std::cout << "To j: " + std::to_string(move.to_j) << std::endl;
//     if (move.capture) {
//         std::cout << "Capture: true" << std::endl;
//     }
//     else {
//         std::cout << "Capture: false"   << std::endl;
//     }

// }

// /**
//  * Updates the board and piece list with the specified move
//  *
//  * TODO put en passant move in separate method?
//  *
//  * @param move a Move that has all fields filled out (move.piece
//  *             should be initialized)
//  */
// void Board::execute_normal_move(Move move) {
//     if (move.from_i < 0 || move.from_j < 0) {
//         throw std::invalid_argument("executing bad coordinates: contact developer");
//     }

//     // remove captured piece from piece list
//     if (move.capture || move.en_passant) {
//         Piece captured_piece = (Piece) (move.en_passant ? board[move.from_i][move.to_j] : board[move.to_i][move.to_j]);
//         int8_t captured_i = move.en_passant ? move.from_i : move.to_i;
//         int8_t captured_j = move.to_j;

//         std::vector<Coordinate> piece_vector = piece_locations[captured_piece];
//         piece_vector.erase(
//             std::remove_if(piece_vector.begin(),
//                            piece_vector.end(),
//                            [captured_i, captured_j](Coordinate c) {
//                                 return (captured_i == c.i && captured_j == c.j);
//                            }),
//             piece_vector.end());

//         // Keep track of captured pieces
//         Square captured_square;
//         captured_square.piece = captured_piece;
//         captured_square.coordinate = {captured_i, captured_j};
//         captured_pieces.push(captured_square);
//     }
//     if (move.en_passant) {
//         board[move.from_i][move.to_j] = 0;
//     }
//     board[move.to_i][move.to_j] = board[move.from_i][move.from_j];
//     board[move.from_i][move.from_j] = 0;

    
//     // possibility of en passant expires after one move unless it's refreshed below
//     if (en_passant_possible) {
//         en_passant_possible = false;
//     }


//     std::vector<Coordinate>::iterator it;
//     it = piece_locations[move.piece].begin();
//     for (; it != piece_locations[move.piece].end(); it++) {
//         if ((*it).i == move.from_i && (*it).j == move.from_j) {

//             // check for potential en passant on the next move
//             if (move.pre_en_passant) {
//                 int8_t ep_i = (move.to_i - move.from_i) / 2 + move.from_i;
//                 int8_t ep_j = move.from_j;
//                 en_passant = {ep_i, ep_j};
//                 en_passant_possible = true;
//             }
//             (*it).i = move.to_i;
//             (*it).j = move.to_j;
//             break;
//         }
//     }


// }

// Move Board::parse_special_move(std::string move) {
//     Move parsed_move;
//     return parsed_move;
// }

// /**
//  * Ensures that a move with at least a specified destination and
//  * piece type is valid and legal.
//  *
//  * @param move a Move with at least the destination, capture, and piece fields
//  *             initialized with valid values, i.e. to_i and to_j >= 0,
//  *             capture == true |false, piece >= WHITE_PAWN
//  *
//  * @return a Move that has the source square fields (from_i, from_j) filled out
//  * @throws TODOexception
//  */
// Move Board::verify_normal_move(Move move) {
//     Move verified_move;
//     if (move.piece >= WHITE_PAWN && move.piece <= WHITE_KING &&
//         board[move.to_i][move.to_j] >= WHITE_PAWN &&
//         board[move.to_i][movegame.to_j] <= WHITE_KING) {
//         throw std::invalid_argument("Cannot move onto your own piece");
//     }
//     if (move.piece >= BLACK_PAWN && move.piece <= BLACK_KING &&
//         board[move.to_i][move.to_j] >= BLACK_PAWN &&
//         board[move.to_i][move.to_j] <= BLACK_KING) {
//         throw std::invalid_argument("Cannot move onto your own piece");
//     }

//     switch (move.piece) {
//         case WHITE_ROOK:
//         case BLACK_ROOK:
//             verified_move = verify_rook_move(move);
//             break;

//         case WHITE_BISHOP:
//         case BLACK_BISHOP:
//             verified_move = verify_bishop_move(move);
//             break;

//         case WHITE_KNIGHT:
//         case BLACK_KNIGHT:
//             verified_move = verify_knight_move(move);
//             break;
//         case WHITE_QUEEN:
//         case BLACK_QUEEN:
//             verified_move = verify_queen_move(move);
//             break;
//         case WHITE_KING:
//         case BLACK_KING:
//             verified_move = verify_king_move(move);
//             break;
//         case WHITE_PAWN:
//         case BLACK_PAWN:
//             verified_move = verify_pawn_move(move);
//             break;
            
//         default:
//             break;
//     }

//     if (white_move && verified_move.capture && !verified_move.en_passant &&
//         (board[verified_move.to_i][verified_move.to_j] < BLACK_PAWN ||
//         board[verified_move.to_i][verified_move.to_j] > BLACK_QUEEN)) {
//         throw std::invalid_argument("No capture available");
//     }

//     if (!white_move && verified_move.capture && !verified_move.en_passant &&
//         (board[verified_move.to_i][verified_move.to_j] < WHITE_PAWN ||
//         board[verified_move.to_i][verified_move.to_j] > WHITE_QUEEN)) {
//         throw std::invalid_argument("No capture available");
//     }
//     return verified_move;
// }



// // TODO: can probably make these methods more general-purpose, i.e.
// // check from square to square instead of a rank or file
// //
// //
// bool Board::clear_between(int8_t ia, int8_t ja, int8_t ib, int8_jb) {
//     if (ia < 0 || ia > 7 || ja < 0 || ja > 7 || ib < 0 || ib > 7 || jb < 0 || jb > 7) {
//         return false;
//     }

//     if (ia == ib || ja == jb)
//         return false;

    
// /**
//  * Check if there are any pieces between board[row][ja] and board[row][jb]
//  *
//  * @param row the row index
//  * @param ja the column index of the first square
//  * @param jb the column index of the second square
//  *
//  * @return true if there are no blockers between the squares, false otherwise
//  */
// bool Board::has_clear_horiz(int8_t row, int8_t ja, int8_t jb) {
//     // We don't allow pieces to not move
//     if (ja == jb) {
//         return false;
//     }
//     for (int8_t j = std::min(ja, jb) + 1; j < std::max(ja, jb); j++) {
//         if (board[row][j] > 0) {
//             return false;
//         }
//     }
//     return true;
// }

// /**
//  * Check if there are any pieces between board[ia][col] and board[ib][col]
//  *
//  * @param col the column index
//  * @param ia the row index of the first square
//  * @param ib the row index of the second square
//  *
//  * @return true if there are no blockers between the squares, false otherwise
//  */
// bool Board::has_clear_vert(int8_t col, int8_t ia, int8_t ib) {
//     // We don't allow pieces to move to their current square 
//     if (ia == ib) {
//         return false;
//     }
//     for (int8_t i = std::min(ia, ib) + 1; i < std::max(ia, ib); i++) {
//         if (board[i][col] > 0) {
//             return false;
//         }
//     }
//     return true;
// }

// /**
//  * Check if there are any pieces between board[ia][ja] and board[ib][jb]
//  *
//  * @param ia the row index of the first square
//  * @param ja the col index of the first square
//  * @param ib the row index of the second square
//  * @param jb the col index of the second square
//  *
//  * @return true if there are no blockers between the squares, false otherwise
//  */
// bool Board::has_clear_diag(int8_t ia, int8_t ja, int8_t ib, int8_t jb) {
//     if (ia == ib && ja == jb) // don't want to divide by zero
//         return false;
//     int8_t incr_i = (ib - ia) / std::abs(ib - ia);
//     int8_t incr_j = (jb - ja) / std::abs(jb - ja);
//     for (int i = ia + incr_i, j = ja + incr_j;
//          i != ib && j != jb;
//          i += incr_i, j += incr_j) {
//         if (board[i][j] > 0) {
//             return false;
//         }
//     }
//     return true;
// }

// /**
//  * Ensure that the given move is valid and legal for a bishop according 
//  * to the positions of the pieces on the board
//  *
//  * @param move a Move with at least the destination, capture, and piece fields
//  *             initialized with valid values, i.e. to_i and to_j >= 0,
//  *             capture == true |false, piece >= WHITE_PAWN
//  *
//  * @return a Move that has the source square fields (from_i, from_j) filled out
//  * @throws TODOexception
//  */
         
// Move Board::verify_bishop_move(Move move) {
//     std::vector<Coordinate>::iterator it = piece_locations[move.piece].begin();
//     bool verified = false;
//     // no from_square specified
//     if (move.from_i < 0 && move.from_j < 0) {
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if (std::abs((*it).i - move.to_i) == std::abs((*it).j - move.to_j)) {
//                 bool is_clear = has_clear_diag((*it).i, (*it).j, move.to_i, move.to_j);

//                 // Checks to see if there was another piece that could have made this move
//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//         }
//     }
//     // rank specified
//     else if (move.from_i >= 0 && move.from_j < 0) {
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).i == move.from_i &&
//                 std::abs((*it).i - move.to_i) == std::abs((*it).j - move.to_j)) {
//                 bool is_clear = has_clear_diag((*it).i, (*it).j, move.to_i, move.to_j);

//                 // Checks to see if there was another piece that could have made this move
//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//         }
//     }
//     // file specified
//     else if (move.from_i < 0 && move.from_j >= 0) {
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).j == move.from_j &&
//                 std::abs((*it).i - move.to_i) == std::abs((*it).j - move.to_j)) {
//                 bool is_clear = has_clear_diag((*it).i, (*it).j, move.to_i, move.to_j);

//                 // Checks to see if there was another piece that could have made this move
//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//         }
//     }
//     else { // both move.from_i and move.from_j were specified
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).i == move.from_i &&
//                 (*it).j == move.from_j && 
//                 std::abs((*it).i - move.to_i) == std::abs((*it).j - move.to_j)) {
//                 bool is_clear = has_clear_diag((*it).i, (*it).j, move.to_i, move.to_j);

//                 // Checks to see if there was another piece that could have made this move
//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//         }
//     }

//     if (!verified) {
//         throw std::invalid_argument("invalid move - placeholder exception");
//     }

//     return move;
// }

// /**
//  * Ensure that the given move is valid and legal for a rook according 
//  * to the positions of the pieces on the board
//  *
//  * @param move a Move with at least the destination, capture, and piece fields
//  *             initialized with valid values, i.e. to_i and to_j >= 0,
//  *             capture == true |false, piece >= WHITE_PAWN
//  *
//  * @return a Move that has the source square fields (from_i, from_j) filled out
//  * @throws TODOexception
//  */
// Move Board::verify_rook_move(Move move) {
//     std::vector<Coordinate>::iterator it = piece_locations[move.piece].begin();
//     bool verified = false;
//     // if 'from' square isn't specified
//     if (move.from_i < 0 && move.from_j < 0) {
//         // We need to check all pieces in case the notation is imprecise
//         for (; it != piece_locations[move.piece].end(); it++) {
//             // if the rook is on the same rank as the 'to' square...
//             if ((*it).i == move.to_i) {
//                 bool is_clear = has_clear_horiz((*it).i, (*it).j, move.to_j);

//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//             else if ((*it).j == move.to_j) {
//                 bool is_clear = has_clear_vert((*it).j, (*it).i, move.to_i);

//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }

//         }
//     }
//     else if (move.from_i >= 0 && move.from_j < 0) {
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).i == move.from_i) {
//                 bool is_clear = has_clear_horiz((*it).i, (*it).j, move.to_j);

//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//         }
//     }
//     else if (move.from_i < 0 && move.from_j >= 0) {
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).j == move.from_j) {
//                 bool is_clear = has_clear_vert((*it).j, (*it).i, move.to_i);

//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//         }
//     }
//     else { // both move.from_i and move.from_j were specified
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).i == move.from_i && (*it).j == move.from_j) {
//                 bool is_clear;
//                 if (move.from_i == move.to_i) {
//                     is_clear = has_clear_horiz(move.from_i, move.from_j, move.to_j);
//                 }
//                 else if (move.from_j == move.to_j) {
//                     is_clear = has_clear_vert(move.from_j, move.from_i, move.to_i);
//                 }
//                 else {
//                     is_clear = false;
//                 }


//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//         }
//     }

//     if (!verified) {
//         throw std::invalid_argument("Invalid move");
//     }

//     return move;
// }

// /**
//  * Ensure that the given move is valid and legal for a rook according 
//  * to the positions of the pieces on the board
//  *
//  * @param move a Move with at least the destination, capture, and piece fields
//  *             initialized with valid values, i.e. to_i and to_j >= 0,
//  *             capture == true |false, piece >= WHITE_PAWN
//  *
//  * @return a Move that has the source square fields (from_i, from_j) filled out
//  * @throws TODOexception
//  */
// Move Board::verify_knight_move(Move move) {
//     std::vector<Coordinate>::iterator it = piece_locations[move.piece].begin();
//     bool verified = false;
//     if (move.from_i < 0 && move.from_j < 0) {
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if (((*it).i == move.to_i + 1 && (*it).j == move.to_j + 2) || // ENE
//                 ((*it).i == move.to_i + 2 && (*it).j == move.to_j + 1) || // NNE
//                 ((*it).i == move.to_i + 2 && (*it).j == move.to_j - 1) || // NNW
//                 ((*it).i == move.to_i + 1 && (*it).j == move.to_j - 2) || // WNW
//                 ((*it).i == move.to_i - 1 && (*it).j == move.to_j - 2) || // WSW
//                 ((*it).i == move.to_i - 2 && (*it).j == move.to_j - 1) || // SSW
//                 ((*it).i == move.to_i - 2 && (*it).j == move.to_j + 1) || // SSE
//                 ((*it).i == move.to_i - 1 && (*it).j == move.to_j + 2)) { // ESE

//                 if (verified) {
//                     throw std::invalid_argument("imprecise notation");
//                 }
//                 move.from_i = (*it).i;
//                 move.from_j = (*it).j;
//                 verified = true;
//             }
//         }
//     }
//     else if (move.from_i >= 0 && move.from_j < 0) {
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).i == move.from_i &&
//                 (
//                     ((*it).i == move.to_i + 1 && (*it).j == move.to_j + 2) || // ENE
//                     ((*it).i == move.to_i + 2 && (*it).j == move.to_j + 1) || // NNE
//                     ((*it).i == move.to_i + 2 && (*it).j == move.to_j - 1) || // NNW
//                     ((*it).i == move.to_i + 1 && (*it).j == move.to_j - 2) || // WNW
//                     ((*it).i == move.to_i - 1 && (*it).j == move.to_j - 2) || // WSW
//                     ((*it).i == move.to_i - 2 && (*it).j == move.to_j - 1) || // SSW
//                     ((*it).i == move.to_i - 2 && (*it).j == move.to_j + 1) || // SSE
//                     ((*it).i == move.to_i - 1 && (*it).j == move.to_j + 2)    // ESE
//                 )) {


//                 if (verified) {
//                     throw std::invalid_argument("imprecise notation");
//                 }
//                 move.from_i = (*it).i;
//                 move.from_j = (*it).j;
//                 verified = true;
//             }
//         }
//     }
//     else if (move.from_i < 0 && move.from_j >= 0) {
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).j == move.from_j &&
//                 (
//                     ((*it).i == move.to_i + 1 && (*it).j == move.to_j + 2) || // ENE
//                     ((*it).i == move.to_i + 2 && (*it).j == move.to_j + 1) || // NNE
//                     ((*it).i == move.to_i + 2 && (*it).j == move.to_j - 1) || // NNW
//                     ((*it).i == move.to_i + 1 && (*it).j == move.to_j - 2) || // WNW
//                     ((*it).i == move.to_i - 1 && (*it).j == move.to_j - 2) || // WSW
//                     ((*it).i == move.to_i - 2 && (*it).j == move.to_j - 1) || // SSW
//                     ((*it).i == move.to_i - 2 && (*it).j == move.to_j + 1) || // SSE
//                     ((*it).i == move.to_i - 1 && (*it).j == move.to_j + 2)    // ESE
//                 )) {


//                 if (verified) {
//                     throw std::invalid_argument("imprecise notation");
//                 }
//                 move.from_i = (*it).i;
//                 move.from_j = (*it).j;
//                 verified = true;
//             }
//         }
//     }
//     else {
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).i == move.from_i && (*it).j == move.from_j &&
//                 (
//                     ((*it).i == move.to_i + 1 && (*it).j == move.to_j + 2) || // ENE
//                     ((*it).i == move.to_i + 2 && (*it).j == move.to_j + 1) || // NNE
//                     ((*it).i == move.to_i + 2 && (*it).j == move.to_j - 1) || // NNW
//                     ((*it).i == move.to_i + 1 && (*it).j == move.to_j - 2) || // WNW
//                     ((*it).i == move.to_i - 1 && (*it).j == move.to_j - 2) || // WSW
//                     ((*it).i == move.to_i - 2 && (*it).j == move.to_j - 1) || // SSW
//                     ((*it).i == move.to_i - 2 && (*it).j == move.to_j + 1) || // SSE
//                     ((*it).i == move.to_i - 1 && (*it).j == move.to_j + 2)    // ESE
//                 )) {


//                 if (verified) {
//                     throw std::invalid_argument("imprecise notation");
//                 }
//                 move.from_i = (*it).i;
//                 move.from_j = (*it).j;
//                 verified = true;
//             }
//         }
//     }

//     if (!verified) {
//         throw std::invalid_argument("cannot make move");
//     }

//     return move;
// }

// /**
// * Ensure that the given move is valid and legal for a queen according 
// * to the positions of the pieces on the board
// *
// * @param move a Move with at least the destination, capture, and piece fields
// *             initialized with valid values, i.e. to_i and to_j >= 0,
// *             capture == true |false, piece >= WHITE_PAWN
// *
// * @return a Move that has the source square fields (from_i, from_j) filled out
// * @throws TODOexception
// */
// Move Board::verify_queen_move(Move move) {
//     std::vector<Coordinate>::iterator it = piece_locations[move.piece].begin();
//     bool verified = false;
//     // if 'from' square isn't specified
//     if (move.from_i < 0 && move.from_j < 0) {
//         // We need to check all pieces in case the notation is imprecise
//         for (; it != piece_locations[move.piece].end(); it++) {
//             // if the queen is on the same rank as the 'to' square...
//             if ((*it).i == move.to_i) {
//                 bool is_clear = has_clear_horiz((*it).i, (*it).j, move.to_j);

//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//             else if ((*it).j == move.to_j) {
//                 bool is_clear = has_clear_vert((*it).j, (*it).i, move.to_i);

//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//             // same diagonal
//             else if (std::abs((*it).i - move.to_i) == std::abs((*it).j - move.to_j)) {
//                 bool is_clear = has_clear_diag((*it).i, (*it).j, move.to_i, move.to_j);

//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//         }
//     }
//     else if (move.from_i >= 0 && move.from_j < 0) {
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).i == move.from_i && (*it).i == move.to_i) {
//                 bool is_clear = has_clear_horiz((*it).i, (*it).j, move.to_j);

//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }

//             else if ((*it).i == move.from_i &&
//                      std::abs((*it).i - move.to_i) == std::abs((*it).j - move.to_j)) {
//                 bool is_clear = has_clear_diag((*it).i, (*it).j, move.to_i, move.to_j);

//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//         }
//     }
//     else if (move.from_i < 0 && move.from_j >= 0) {
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).j == move.from_j && (*it).j == move.to_j) {
//                 bool is_clear = has_clear_vert((*it).j, (*it).i, move.to_i);

//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//             else if ((*it).j == move.from_j &&
//                      std::abs((*it).i - move.to_i) == std::abs((*it).j - move.to_j)) {
//                 bool is_clear = has_clear_diag((*it).i, (*it).j, move.to_i, move.to_j);

//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//         }
//     }
//     else { // both move.from_i and move.from_j were specified
//         for (; it != piece_locations[move.piece].end(); it++) {
//             if ((*it).i == move.from_i && (*it).j == move.from_j) {
//                 bool is_clear;
//                 if (move.from_i == move.to_i) {
//                     is_clear = has_clear_horiz(move.from_i, move.from_j, move.to_j);
//                 }
//                 else if (move.from_j == move.to_j) {
//                     is_clear = has_clear_vert(move.from_j, move.from_i, move.to_i);
//                 }
//                 else if (std::abs(move.from_i - move.to_i) == std::abs(move.from_j - move.to_j)) {
//                     is_clear = has_clear_diag(move.from_i, move.from_j, move.to_i, move.to_j);
//                 }
//                 else {
//                     is_clear = false;
//                 }


//                 if (is_clear && verified) {
//                     throw std::invalid_argument("Imprecise notation - placeholder exception");
//                 }

//                 if (is_clear) {
//                     move.from_i = (*it).i;
//                     move.from_j = (*it).j;

//                     verified = true;
//                 }
//             }
//         }
//     }

//     if (!verified) {
//         throw std::invalid_argument("Invalid move");
//     }

//     return move;
// }

// /**
// * Ensure that the given move is valid and legal for a king according 
// * to the positions of the pieces on the board
// *
// * @param move a Move with at least the destination, capture, and piece fields
// *             initialized with valid values, i.e. to_i and to_j >= 0,
// *             capture == true |false, piece >= WHITE_PAWN
// *
// * @return a Move that has the source square fields (from_i, from_j) filled out
// * @throws TODOexception
// */
// Move Board::verify_king_move(Move move) {
//     bool verified = false;
//     // There should only be one king
//     for (std::vector<Coordinate>::iterator it = piece_locations[move.piece].begin();
//          it != piece_locations[move.piece].end();
//          it++) {
//         int8_t king_i = (*it).i;
//         int8_t king_j = (*it).j;
//         if ((king_i == move.to_i + 1 && king_j == move.to_j) || // N
//             (king_i == move.to_i + 1 && king_j == move.to_j + 1) || // NE
//             (king_i == move.to_i && king_j == move.to_j + 1) || // E
//             (king_i == move.to_i - 1 && king_j == move.to_j + 1) || // SE
//             (king_i == move.to_i - 1 && king_j == move.to_j) || // S
//             (king_i == move.to_i - 1 && king_j == move.to_j - 1) || // SW
//             (king_i == move.to_i && king_j == move.to_j - 1) || // W
//             (king_i == move.to_i + 1 && king_j == move.to_j - 1)) { // NW

//             verified = true;

//             move.from_i = king_i;
//             move.from_j = king_j;
//         }
//     }

//     if (!verified) {
//         throw std::invalid_argument("Invalid move");
//     }

//     return move;
// }

// /**
// * Ensure that the given move is valid and legal for a pawn according 
// * to the positions of the pieces on the board
// *
// * @param move a Move with at least the destination, capture, and piece fields
// *             initialized with valid values, i.e. to_i and to_j >= 0,
// *             capture == true |false, piece >= WHITE_PAWN
// *
// * @return a Move that has the source square fields (from_i, from_j) filled out
// * @throws TODOexception
// */
// Move Board::verify_pawn_move(Move move) {
//     if (move.to_i >= 7 || move.to_i <= 0) {
//         throw std::invalid_argument("Specify a promotion");
//     }
//     bool verified = false;
//     int8_t start_rank, move_incr;
//     if (move.piece == WHITE_PAWN) {
//         start_rank = 1;
//         move_incr = 1;
//     }
//     else {
//         start_rank = 6;
//         move_incr = -1;
//     }

//     if (!move.capture) {
//         for (std::vector<Coordinate>::iterator it = piece_locations[move.piece].begin();
//              it != piece_locations[move.piece].end();
//              it++) {
//             if ((*it).j == move.to_j) {
//                 if ((*it).i + move_incr == move.to_i ||
//                     ((*it).i == start_rank && (*it).i + 2 * move_incr == move.to_i)) {
//                     std::cout << "verified pawn";

//                     verified = has_clear_vert((*it).j, (*it).i, move.to_i + move_incr);
//                     if (verified) {
//                         move.from_i = (*it).i;
//                         move.from_j = (*it).j;

//                         if (std::abs(move.to_i - move.from_i) == 2) {
//                             move.pre_en_passant = true;
//                         }
//                         break;
//                     }
//                 }
//             }
//         }
//     }
//     else {
//         if (move.from_j != move.to_j + 1 && move.from_j != move.to_j - 1) {
//             throw std::invalid_argument("Pawn can't do that");
//         }

//         bool en_passant_capture = (en_passant_possible && move.to_i == en_passant.i && move.to_j == en_passant.j);

//         if (board[move.to_i][move.to_j] == 0 && !en_passant_capture) {
//             throw std::invalid_argument("No capture available");
//         }

//         for (std::vector<Coordinate>::iterator it = piece_locations[move.piece].begin();
//              it != piece_locations[move.piece].end();
//              it++) {

//             if ((*it).j == move.from_j && (*it).i + move_incr == move.to_i) {
//                 move.from_i = (*it).i;
//                 move.from_j = (*it).j;

//                 move.en_passant = en_passant_capture;

//                 verified = true;
//             }
//         }
//     }

//     if (!verified) {
//         throw std::invalid_argument("Invalid move - end of pawn verification");
//     }
//     return move;
// }









// /**
//  * Emulates a finite state machine to parse the input string
//  * of algebraic notation from the end to the beginning
//  *
//  * @param move a string of the form
//  *             [RNBQK]?[a-h]?[1-8]?x?[a-h][1-8]
//  *
//  * @return a Move with the appropriate variables filled out
//  */
// Move Board::parse_normal_move(std::string move) {
//     Move parsed_move;

//     int state;
//     const int to_file = 1, to_rank = 2, capture = 3, from_file = 4, from_rank = 5, piece = 6;

//     std::string::const_reverse_iterator it = move.crbegin();

//     state = 0;
//     while (it != move.crend()) {
//         switch (state) {
//             case 0: 
//                 if (*it >= '1' && *it <= '8') {
//                     state = to_rank;
//                 }
//                 else {
//                     throw std::invalid_argument("invalid notation");
//                 }
//                 break;

//             case to_rank:
//                 parsed_move.to_i = *it - '1';

//                 it++;
//                 if (*it >= 'a' && *it <= 'h') {
//                     state = to_file;
//                 }
//                 else {
//                     throw std::invalid_argument("invalid notation");
//                 }
//                 break;

//             case to_file:
//                 parsed_move.to_j = *it - 'a';

//                 it++;
//                 /**
//                  * Needing to set
//                  * parsed_move.capture = [true | false] virtually 
//                  * doubles the number of following states, but
//                  * practically we can just have parsed_move.capture
//                  * differentiate between otherwise identical states
//                  */
//                 if (*it == 'x') {
//                     parsed_move.capture = true;
//                     state = capture;
//                 }
//                 else if (*it >= '1' && *it <= '8') {
//                     parsed_move.capture = false;
//                     state = from_rank;
//                 }
//                 else if (*it >= 'a' && *it <= 'h') {
//                     parsed_move.capture = false;
//                     state = from_file;
//                 }
//                 else if (*it == 'R' || *it == 'N' ||
//                          *it == 'B' || *it == 'Q' ||
//                          *it == 'K') {
//                     parsed_move.capture = false;
//                     state = piece;
//                 }
//                 else if (it == move.crend()) {
//                     parsed_move.piece_name = 'P';
//                     state = 100;
//                 }
//                 else {
//                     throw std::invalid_argument("invalid notation");
//                 }
 
//                 break;

//             case capture:
//                 /** 
//                  * This case is essentially a repeat of the
//                  * else-if statements in case to_file. This
//                  * 'capture' case is necessary to make sure
//                  * we haven't reached the beginning of the string
//                  * yet.
//                  */
//                 it++;
//                 if (*it >= '1' && *it <= '8') {
//                     state = from_rank;
//                 }
//                 else if (*it >= 'a' && *it <= 'h') {
//                     state = from_file;
//                 }
//                 else if (*it == 'R' || *it == 'N' ||
//                          *it == 'B' || *it == 'Q' ||
//                          *it == 'K') {
//                     state = piece;
//                 }
//                 else {
//                     throw std::invalid_argument("invalid notation");
//                 }
//                 break;

//             case from_rank:
//                 parsed_move.from_i = *it - '1';

//                 it++;
//                 if (*it >= 'a' && *it <= 'h') {
//                     state = from_file;
//                 }
//                 else if (*it == 'R' || *it == 'N' ||
//                          *it == 'B' || *it == 'Q' ||
//                          *it == 'K') {
//                     state = piece;
//                 }
//                 else {
//                     throw std::invalid_argument("invalid notation");
//                 }
//                 break;

//             case from_file:
//                 parsed_move.from_j = *it - 'a';

//                 it++;
//                 if (*it == 'R' || *it == 'N' ||
//                     *it == 'B' || *it == 'Q' ||
//                     *it == 'K') {
//                     state = piece;
//                 }
//                 else if (it == move.crend()) {
//                     parsed_move.piece_name = 'P';
//                     state = 100;
//                 }
//                 else {
//                     throw std::invalid_argument("invalid notation");
//                 }
//                 break;

//             case piece:
//                 parsed_move.piece_name = *it;

//                 it++;

//                 state = 100;
//                 break;

//             default:
//                 throw std::invalid_argument("unknown state when parsing");
//                 break;
//         }
//     }

//     return parsed_move;
// }

// bool Board::king_in_check(Piece king) {
//     assert(king == WHITE_KING || king == BLACK_KING);

//     uint8_t pawn, king;

//     if (king == WHITE_KING) {
//         pawn = BLACK_PAWN;
//         king = BLACK_KING;
//     }
//     else {
//         pawn = WHITE_PAWN;
//         king = WHITE_PAWN;
//     }

//     for (int i = pawn; i <= king; i++) {
//         std::vector<Coordinate>::iterator it = piece_locations[i].begin();
//         for (; it != piece_locations[i].end(); it++) {
//             if () ;
//         }
//     }
// }
        

    


