#include <exception>
#include <cmath>
#include <string>
#include <cassert>
#include "chess_gui.h"

Player::Player(std::string name, Board &chessboard, Color color)
    : _name(name), _chessboard(chessboard), _color(color)
{
    _en_passant_rank = (color == Color::White ? 4 : 3);
    _direction = (color == Color::White ? 1 : -1);
}

void Player::make_valid_move(Move move)
{

    std::cout << move;
    _chessboard.move(move.source, move.destination);
}
// TODO add history to parameter
void Player::make_move(std::string move_notation)
{
    Move final_move;

    final_move = Parser::parse_algebraic_notation(move_notation);

    final_move = fill_move(final_move);

    // TODO remove after debugging
    assert(final_move.source.file >= 0);
    assert(final_move.source.rank >= 0);

    bool is_valid_move = verify_move(final_move);

    if (is_valid_move)
    {
        make_valid_move(final_move);
    }
    else
    {
        DEBUG("invalid move");
        throw std::logic_error("invalid move");
        // throw
    }
}

bool Player::is_attacked(Coordinate destination, Board &verification_board)
{
    for (int file = 0; file < 8; file++)
    {
        for (int rank = 0; rank < 8; rank++)
        {
            Square square = verification_board.get_piece(Coordinate{file, rank});
            if (square.occupied && (square.piece.color == opposite_color(verification_board.get_piece(destination).piece.color)))
            {
                // TODO a hack. refactor is_valid_pawn_move to make this cleaner
                bool is_check = is_valid_capture(Coordinate{file, rank}, destination);

                if (is_check)
                {
                    std::string message = std::to_string(file) + ", " + std::to_string(rank);
                    std::string destination_string = std::to_string(destination.file) + ", " + std::to_string(destination.rank);
                    DEBUG(message);
                    DEBUG(destination_string);
                    return true;
                }
            }
        }
    }
    return false;
}

bool Player::verify_move(Move move)
{
    //throw std::exception();
    Board verification_board = _chessboard;
    Coordinate king_location;

    if ((bool)(move.move_type & MoveType::Normal))
    {
        verification_board.move(move.source, move.destination);
        for (int file = 0; file < 8; file++)
        {
            for (int rank = 0; rank < 8; rank++)
            {
                Square square = verification_board.get_piece(Coordinate{file, rank});
                if (square.occupied &&
                    square.piece.piece_type == PieceType::King &&
                    square.piece.color == _color)
                {
                    king_location = Coordinate{file, rank};
                }
            }
        }
    }
    else if ((bool)(move.move_type & MoveType::Kingside_Castle))
    {
        Coordinate intermediate_location = {move.source.file + 1, move.source.rank};
        verification_board.move(move.source, intermediate_location);
        if (is_attacked(intermediate_location, verification_board))
        {
            return false;
        }
        verification_board.move(intermediate_location, move.destination);
        king_location = move.destination;
    }
    else if ((bool)(move.move_type & MoveType::Queenside_Castle))
    {
        Coordinate intermediate_location = {move.source.file - 1, move.source.rank};
        verification_board.move(move.source, intermediate_location);
        if (is_attacked(intermediate_location, verification_board))
        {
            return false;
        }

        Coordinate second_intermediate_location = {move.source.file - 2, move.source.rank};
        verification_board.move(intermediate_location, second_intermediate_location);
        if (is_attacked(intermediate_location, verification_board))
        {
            return false;
        }
        verification_board.move(move.source, move.destination);
        king_location = move.destination;
    }
    if (is_attacked(king_location, verification_board))
    {
        std::string king_loc_string = std::to_string(king_location.file) + ", " + std::to_string(king_location.rank);
        DEBUG(king_loc_string);
        return false;
    }
    // TODO check checkmate

    if ((bool) (move.move_type & MoveType::Kingside_Castle))
    {
        // TODO check for past history of castle and king or rook moves 
        // TODO different classes for black and white players
        if (_color == Color::White)
        {
           if (!is_clear_path(Coordinate{4, 0}, Coordinate{7, 0}))
           {
               return false; 
           }
        }
        else if (_color == Color::Black)
        {
            if (!is_clear_path(Coordinate{4, 7}, Coordinate{7, 7}))
            {
                return false;
            }
        }
    }
    else if ((bool) (move.move_type & MoveType::Queenside_Castle))
    {
        if (_color == Color::White)
        {
           if (!is_clear_path(Coordinate{4, 0}, Coordinate{0, 0}))
           {
               return false; 
           }
        }
        else if (_color == Color::Black)
        {
            if (!is_clear_path(Coordinate{4, 7}, Coordinate{0, 7}))
            {
                return false;
            }
        }

    }
    return true;
}

// destination and moving piece must be filled in
Move Player::fill_move(Move partial_move)
{
    if ((bool)(partial_move.move_type & MoveType::Normal))
    {
        if (_chessboard.get_piece(partial_move.destination).piece.piece_type != PieceType::None)
        {
            partial_move.move_type = partial_move.move_type | MoveType::Capture; // TODO remove this
        }

        std::vector<Coordinate> potential_sources = get_source_squares(partial_move.destination, partial_move.piece_type);
        // TODO refactor: delete Coordinates that don't match criteria and then check for size() == 1
        // If neither source file nor source rank is specified
        if (partial_move.source.file < 0 && partial_move.source.rank < 0)
        {
            DEBUG("no source specified");
            if (partial_move.piece_type == PieceType::None)
            {
                // throw
                // TODO don't need to check because parser should guarantee this
            }
            if (potential_sources.size() == 1)
            {
                DEBUG("in happy case");
                partial_move.source = potential_sources.front();
                DEBUG(std::to_string(partial_move.source.file));
                DEBUG(std::to_string(partial_move.source.rank));
            }
            else
            {
                throw std::logic_error("ambiguous notation");
                DEBUG("in bad case");
                // throw
            }
        }
        // If only source file is specified
        else if (partial_move.source.file >= 0 && partial_move.source.rank < 0)
        {
            DEBUG("source file specified");
            std::vector<Coordinate>::iterator it = potential_sources.begin();
            Coordinate source_square;
            bool found_matching_coordinate = false;
            for (it; it != potential_sources.end(); it++)
            {
                if ((*it).file == partial_move.source.file)
                {
                    source_square = *it;
                    if (found_matching_coordinate)
                    {
                        throw std::logic_error("ambiguous notation");
                        // throw - more than one possible source, so notation is ambiguous
                    }
                    else
                    {
                        found_matching_coordinate = true;
                    }
                }
            }

            if (found_matching_coordinate)
            {
                partial_move.source = source_square;
            }
            else
            {
                throw std::logic_error("no such possible move");
                // throw
            }
        }
        // If only source rank is specified
        else if (partial_move.source.file < 0 && partial_move.source.rank >= 0)
        {
            DEBUG("source rank specified");
            std::vector<Coordinate>::iterator it = potential_sources.begin();
            Coordinate source_square;
            bool found_matching_coordinate = false;
            for (it; it != potential_sources.end(); it++)
            {
                if ((*it).rank == partial_move.source.rank)
                {
                    source_square = *it;
                    if (found_matching_coordinate)
                    {
                        throw std::logic_error("ambiguous notation");
                        // throw - more than one possible source, so notation is ambiguous
                    }
                    else
                    {
                        found_matching_coordinate = true;
                    }
                }
            }

            if (found_matching_coordinate)
            {
                partial_move.source = source_square;
            }
            else
            {
                throw std::logic_error("no such possible move");
                // throw
            }
        }
        // If both source file and source rank are specified
        else
        {
            DEBUG("both source file and rank specified");
            std::vector<Coordinate>::iterator it = potential_sources.begin();
            Coordinate source_square;
            bool found_matching_coordinate = false;
            for (it; it != potential_sources.end(); it++)
            {
                if ((*it).rank == partial_move.source.rank && (*it).file == partial_move.source.file)
                {
                    source_square = *it;
                    if (found_matching_coordinate)
                    {
                        throw std::logic_error("ambiguous notation");
                        // throw - more than one possible source, so notation is ambiguous
                    }
                    else
                    {
                        found_matching_coordinate = true;
                    }
                }
            }

            if (found_matching_coordinate)
            {
                partial_move.source = source_square;
            }
            else
            {
                throw std::logic_error("no such possible move");
                // throw
            }
        }
    }

    return partial_move;
}

/**
 * Determines whether the path between two squares is clear of obstacles.
 * 
 * The path does not include the two specified squares.
 * The two squares must be on the same file or rank or diagonal from each other;
 * the result is undefined if this requirement is not met.
 * 
 * @param source the starting square
 * @param destination the ending square
 * 
 * @return true if there is a clear path, else false
 */
bool Player::is_clear_path(Coordinate source, Coordinate destination)
{
    int file_difference = destination.file - source.file;
    int rank_difference = destination.rank - source.rank;

    int file_direction = file_difference == 0 ? 0 : file_difference / std::abs(file_difference);
    int rank_direction = rank_difference == 0 ? 0 : rank_difference / std::abs(rank_difference);

    int path_file = source.file + file_direction;
    int path_rank = source.rank + rank_direction;

    while (path_file != destination.file && path_rank != destination.rank)
    {
        if (_chessboard.get_piece(Coordinate{path_file, path_rank}).occupied)
        {
            return false;
        }
        path_file += file_direction;
        path_rank += rank_direction;
    }

    return true;
}

std::vector<Coordinate> Player::get_source_squares(Coordinate destination, PieceType piece_type)
{
    std::vector<Coordinate> potential_sources;
    for (int file = 0; file < 8; file++)
    {
        for (int rank = 0; rank < 8; rank++)
        {
            Piece square = _chessboard.get_piece(Coordinate{file, rank}).piece;
            if (square.piece_type == piece_type && square.color == _color)
            {
                potential_sources.push_back(Coordinate{file, rank});
            }
        }
    }

    DEBUG(std::to_string(potential_sources.size()));

    std::vector<Coordinate> actual_sources;
    for (Coordinate &potential_source : potential_sources)
    {
        if (is_valid_move(piece_type, potential_source, destination) || is_valid_capture(potential_source, destination))
        {
            actual_sources.push_back(potential_source);
        }
    }

    return actual_sources;
}

/**
 * Determines whether a piece on the source square can make a capture on the destination square
 * 
 * @param source the starting square of the piece
 * @param destination the ending square for the piece
 * @return true if the piece can make the capture, else false
 */
bool Player::is_valid_capture(Coordinate source, Coordinate destination)
{
    Piece capturing_piece = _chessboard.get_piece(source).piece;
    Square destination_square = _chessboard.get_piece(destination);
    if (destination_square.occupied && destination_square.piece.color == capturing_piece.color)
    {
        return false;
    }
    bool is_valid_capture;
    switch (capturing_piece.piece_type)
    {
    case PieceType::Pawn:
        is_valid_capture = is_valid_pawn_capture(source, destination);
        break;
    case PieceType::Rook:
        is_valid_capture = is_valid_rook_move(source, destination);
        break;
    case PieceType::Knight:
        is_valid_capture = is_valid_knight_move(source, destination);
        break;
    case PieceType::Bishop:
        is_valid_capture = is_valid_bishop_move(source, destination);
        break;
    case PieceType::Queen:
        is_valid_capture = is_valid_queen_move(source, destination);
        break;
    case PieceType::King:
        is_valid_capture = is_valid_king_move(source, destination);
        break;
    default:
        // TODO throw
        break;
    }

    if (is_valid_capture &&
        destination_square.occupied &&
        destination_square.piece.color != Color::None)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Determines whether a rook can make a move between two squares.
 * 
 * @param source the starting square of the rook
 * @param destination the ending square for the rook
 * @return true if the rook can move up to (but not including) the destination, else false
 */
bool Player::is_valid_rook_move(Coordinate source, Coordinate destination)
{
    bool is_same_rank = (source.rank == destination.rank);
    bool is_same_file = (source.file == destination.file);
    bool is_clear = is_clear_path(source, destination);
    if ((is_same_rank || is_same_file) && is_clear)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Determines whether a knight can make a move between two squares.
 * 
 * @param source the starting square of the knight
 * @param destination the ending square for the knight
 * @return true if the knight can move to the destination, else false
 */
bool Player::is_valid_knight_move(Coordinate source, Coordinate destination)
{
    int file_distance = std::abs(destination.file - source.file);
    int rank_distance = std::abs(destination.rank - source.rank);

    std::string debug_message = std::to_string(file_distance) + ", " + std::to_string(rank_distance);
    DEBUG(debug_message);
    if ((file_distance != 0 && rank_distance != 0) &&
        (file_distance + rank_distance == 3))
    {
        DEBUG("in happy path");
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Determines whether a bishop can make a move between two squares.
 * 
 * @param source the starting square of the bishop 
 * @param destination the ending square for the bishop 
 * @return true if the bishop can move up to (but not including) the destination, else false
 */
bool Player::is_valid_bishop_move(Coordinate source, Coordinate destination)
{
    int file_distance = std::abs(destination.file - source.file);
    int rank_distance = std::abs(destination.rank - source.rank);

    bool is_diagonal = (file_distance == rank_distance);
    bool is_clear = is_clear_path(source, destination);

    if (is_diagonal && is_clear)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Determines whether a queen can make a move between two squares.
 * 
 * @param source the starting square of the queen 
 * @param destination the ending square for the queen 
 * @return true if the queen can move up to (but not including) the destination, else false
 */
bool Player::is_valid_queen_move(Coordinate source, Coordinate destination)
{
    bool is_valid_orthogonal_move = is_valid_rook_move(source, destination);
    bool is_valid_diagonal_move = is_valid_bishop_move(source, destination);

    if (is_valid_orthogonal_move || is_valid_diagonal_move)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Determines whether a king can make a move between two squares.
 * 
 * @param source the starting square of the king
 * @param destination the ending square for the king
 * @return true if the king can move up to (but not including) the destination, else false
 */
bool Player::is_valid_king_move(Coordinate source, Coordinate destination)
{
    int file_difference = destination.file - source.file;
    int rank_difference = destination.rank - source.rank;
    int file_distance = std::abs(file_difference);
    int rank_distance = std::abs(rank_difference);

    if ((file_distance == 1 && rank_distance == 0) ||
        (file_distance == 0 && rank_distance == 1) ||
        (file_distance == 1 && rank_distance == 1))
    {
        return true;
    }

    else
    {
        return false;
    }
}

/**
 * Determines whether a pawn can make a move between two squares.
 * // TODO refactor to take in color
 * 
 * @param source the starting square of the pawn
 * @param destination the ending square for the pawn
 * @return true if the pawn can move up to (but not including) the destination, else false
 */
bool Player::is_valid_pawn_move(Coordinate source, Coordinate destination)
{
    int rank_difference = destination.rank - source.rank;
    if (rank_difference == 0)
    {
        return false;
    }
    bool is_same_file = (destination.file == source.file);
    int move_direction = rank_difference / std::abs(rank_difference);
    bool is_correct_direction = (move_direction == _direction);

    if (std::abs(rank_difference) == 1)
    {
        return is_same_file && is_correct_direction;
    }
    else if (std::abs(rank_difference) == 2)
    {
        bool is_correct_starting_rank = false;
        if (_color == Color::Black)
        {
            is_correct_starting_rank = (source.rank == 6);
        }
        else if (_color == Color::White)
        {
            is_correct_starting_rank = (source.rank == 1);
        }
        bool is_clear = is_clear_path(source, destination);

        return is_same_file && is_correct_direction && is_correct_starting_rank && is_clear;
    }
    else
    {
        return false;
    }
}

// TODO don't need this
/**
 * Determines if the moving_piece can move from source to destination.
 * 
 * For a move to be valid, there must be no pieces between source and destination
 * (for sliding pieces) and the destination piece must be unoccupied.
 * 
 * @param moving_piece the type of piece that is moving
 * @param source the starting square of the piece
 * @param destination the ending square for the piece
 * @return true if the piece can make the move, else false
 */
bool Player::is_valid_move(PieceType moving_piece, Coordinate source, Coordinate destination)
{
    bool is_valid = false;
    switch (moving_piece)
    {
    case PieceType::Pawn:
        is_valid = is_valid_pawn_move(source, destination);
        break;
    case PieceType::Rook:
        is_valid = is_valid_rook_move(source, destination);
        break;
    case PieceType::Knight:
        is_valid = is_valid_knight_move(source, destination);
        break;
    case PieceType::Bishop:
        is_valid = is_valid_bishop_move(source, destination);
        break;
    case PieceType::Queen:
        is_valid = is_valid_queen_move(source, destination);
        break;
    case PieceType::King:
        is_valid = is_valid_king_move(source, destination);
        break;
    }

    bool empty_destination = !_chessboard.get_piece(destination).occupied;
    DEBUG(std::to_string(empty_destination));
    return is_valid && empty_destination;
}

/**
 * Determines if a pawn can capture from source to destination.
 * 
 * @param source the starting square of the pawn
 * @param destination the ending square for the pawn
 * @return true if the pawn can make the capture, else false
 */
bool Player::is_valid_pawn_capture(Coordinate source, Coordinate destination)
{
    // TODO en passant
    int file_distance = std::abs(destination.file - source.file);
    int rank_distance = std::abs(destination.rank - source.rank);

    bool is_one_diagonal = (file_distance == 1 && rank_distance == 1);
    bool is_correct_direction = (destination.rank - source.rank == _direction);

    if (is_one_diagonal && is_correct_direction)
    {
        return true;
    }
    else
    {
        return false;
    }
}
