#include <string>
#include "chess_gui.h"

namespace Parser
{

/**
 * Helper methods for parse_algebraic_notation()
 */
    namespace
    {
        Move parse_normal_move(std::string notation);
        Move parse_destination_rank(std::string notation);
        Move parse_destination_file(std::string notation);
        Move parse_capture(std::string notation);
        Move parse_moving_piece(std::string notation);
        Move parse_source_rank(std::string notation);
        Move parse_source_file(std::string notation);
    }
/**
 * Parses a valid chess algebraic notation string into a Move struct.
 * 
 * @param notation a valid algebraic notation for a move
 * @return a Move that contains all the information represented in the notation
 * 
 * @throws TODO if notation is not valid
 */
Move parse_algebraic_notation(std::string notation)
{
    Move parsed_move;
    if (notation == "O-O" || notation == "0-0-0")
    {
        // castle king side
    }
    else if (notation == "O-O-O" || notation == "0-0-0")
    {
        // castle queen side
    }
    else if (notation == "ep" /* ends in e.p. */)
    {
        // en passant
    }
    else if (notation == "Q" /* ends in B, N, R, or Q */)
    {
        // promotion
    }
    else if (notation.back() == '+')
    {
        notation.pop_back();
        parsed_move = parse_normal_move(notation);
        parsed_move.move_type = parsed_move.move_type | MoveType::Check;
        return parsed_move;
    }
    else if (notation.back() == '#')
    {
        notation.pop_back();
        parsed_move = parse_normal_move(notation);
        parsed_move.move_type = parsed_move.move_type | MoveType::Checkmate;
        return parsed_move;
    }
    else
    {
        parsed_move = parse_normal_move(notation);
        return parsed_move; // TODO
    }
}

// TODO return reference to Move ?
// TODO use substring
namespace
{
/**
 * Parses algebraic notation that represents a non-castle, non-(en passant), non-promotion move.
 * 
 * @param notation a valid algebraic notation for a move
 * @return a Move that contains all the information represented in the notation
 */
Move parse_normal_move(std::string notation)
{
    if (notation.back() >= '1' && notation.back() <= '8')
    {
        Move parsed_move = parse_destination_rank(notation);
        parsed_move.move_type = parsed_move.move_type | MoveType::Normal;
        return parsed_move;
    }
    else
    {
        // throw
    }
}

/**
 * Parses algebraic notation whose last character represents the rank of the destination square.
 * 
 * @param notation a valid algebraic notation for a move
 * @return a Move that contains all the information represented in the notation
 */
Move parse_destination_rank(std::string notation)
{
    char destination_rank = notation.back() - '1';

    notation.pop_back();
    if (notation.back() >= 'a' && notation.back() <= 'h')
    {
        Move parsed_move = parse_destination_file(notation);
        parsed_move.destination.rank = (int) destination_rank;
        return parsed_move;
    }
    else
    {
        // throw
    }
}

/**
 * Parses algebraic notation whose last character represents the file of the destination square.
 * 
 * @param notation a valid partial algebraic notation for a move
 * @return a Move that contains all the information represented in the partial notation
 */
Move parse_destination_file(std::string notation)
{
    char destination_file = notation.back() - 'a';
    notation.pop_back();
    Move parsed_move;

    if (notation.empty() ||
        notation.back() == 'K' ||
        notation.back() == 'Q' ||
        notation.back() == 'R' ||
        notation.back() == 'B' ||
        notation.back() == 'N')
    {
        parsed_move = parse_moving_piece(notation);
    }
    else if (notation.back() == 'x' || notation.back() == 'X')
    {
        parsed_move = parse_capture(notation);
    }
    else if (notation.back() >= 'a' && notation.back() <= 'h')
    {
        parsed_move = parse_source_file(notation);
    }
    else if (notation.back() >= '1' && notation.back() <= '8')
    {
        parsed_move = parse_source_rank(notation);
    }
    else
    {
        // throw
    }

    parsed_move.destination.file = (int)destination_file;
    return parsed_move;
}

/**
 * Parses algebraic notation whose last character represents a capture.
 * 
 * @param notation a valid partial algebraic notation for a move
 * @return a Move that contains all the information represented in the partial notation
 */ 
Move parse_capture(std::string notation)
{
    notation.pop_back();
    Move parsed_move;
    if (notation.back() == 'K' ||
        notation.back() == 'Q' ||
        notation.back() == 'R' ||
        notation.back() == 'B' ||
        notation.back() == 'N')
    {

        parsed_move = parse_moving_piece(notation);
    }
    else if (notation.back() >= 'a' && notation.back() <= 'h')
    {
        parsed_move = parse_source_file(notation);
    }
    else if (notation.back() >= '1' && notation.back() <= '8')
    {
        parsed_move = parse_source_rank(notation);
    }
    else
    {
        // throw
    }

    parsed_move.move_type = parsed_move.move_type | MoveType::Capture;
    return parsed_move;
}

/**
 * Parses algebraic notation whose last character represents the rank of the source square.
 * 
 * @param notation a valid partial algebraic notation for a move
 * @return a Move that contains all the information represented in the partial notation
 */
Move parse_source_rank(std::string notation)
{
    char source_rank = notation.back() - '1';
    notation.pop_back();
    Move parsed_move;

    if (notation.back() == 'K' ||
        notation.back() == 'Q' ||
        notation.back() == 'R' ||
        notation.back() == 'B' ||
        notation.back() == 'N')
    {

        parsed_move = parse_moving_piece(notation);
    }
    else if (notation.back() >= 'a' && notation.back() <= 'h')
    {
        parsed_move = parse_source_file(notation);
    }
    else
    {
        // throw
    }

    parsed_move.source.rank = source_rank;
    return parsed_move;
}

/**
 * Parses algebraic notation whose last character represents the file of the source square.
 * 
 * @param notation a valid partial algebraic notation for a move
 * @return a Move that contains all the information represented in the partial notation
 */
Move parse_source_file(std::string notation)
{
    char source_file = notation.back() - 'a';
    notation.pop_back();
    Move parsed_move;

    if (notation.empty() ||
        notation.back() == 'K' ||
        notation.back() == 'Q' ||
        notation.back() == 'R' ||
        notation.back() == 'B' ||
        notation.back() == 'N')
    {

        parsed_move = parse_moving_piece(notation);
    }
    else
    {
        // throw
    }

    parsed_move.source.file = source_file;
    return parsed_move;
}

/**
 * Parses algebraic notation whose last character represents a chess piece.
 * 
 * @param notation a valid partial algebraic notation for a move
 * @return a Move that contains all the information represented in the partial notation
 */
Move parse_moving_piece(std::string notation)
{
    std::unordered_map<char, PieceType> piece_from_notation =
        {
            {'K', PieceType::King},
            {'Q', PieceType::Queen},
            {'B', PieceType::Bishop},
            {'N', PieceType::Knight},
            {'R', PieceType::Rook}};

    Move parsed_move{Coordinate{-1, -1}, Coordinate{-1, -1}, PieceType::None, MoveType::None};
    if (notation.empty())
    {
        parsed_move.piece_type = PieceType::Pawn;
    }
    else
    {
        char piece_notation = notation.back();
        parsed_move.piece_type = piece_from_notation[piece_notation];

        notation.pop_back();
        if (!notation.empty())
        {
            // throw
        }
    }

    return parsed_move;
}
}
}
