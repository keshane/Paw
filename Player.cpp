#include "chess_gui.h"

Player::Player(std::string name, Board* chessboard, Color color)
    : this->name(name), this->chessboard(chessboard), this->coor(color);
{
}

void Player::make_move(std::string move_notation) {
    Move final_move;
    
    final_move = this->move_parser.parse_algebraic_notation(move_notation);

    final_move = fill_move(final_move);

    bool is_valid_move = verify_move(final_move);

    if (is_valid_move) {
        make_valid_move(final_move);
    }
    else {
        // throw
    }

}

Move Player::fill_move(Move partial_move) {
    if (partial_move.move_type & MoveType.Normal) {
        if (this->chessboard.get_piece(partial_move.destination).piece_type != PieceType.None) {
            partial_move.move_type |= MoveType.Capture;
        }

        if (partial_move.source.file < 0 && partial_move.source.rank < 0) {
            if (partial_move.piece.piece_type == PieceType.None) {
                // throw
            }
            Coordinate[] potential_sources = get_source_squares(partial_move.destination, partial_move.piece.piece_type);
            // TODO find source square

        }

    }
}

// TODO refactor this big af, redundant method
std::vector<Coordinate> Player::get_source_squares(Coordinate destination, PieceType piece_type) {
    std::vector<Coordinate> potential_sources;
    switch (piece_type) {
        case PieceType.Pawn:
            // pawn logic
            break;
        case PieceType.Rook:
            for (int8_t i = source.file - 1; i >= 0; i--) {
                Piece square = this->chessboard.get_piece(Coordinate(i, destination.rank));
                if (square.piece_type == PieceType.Rook && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, destination.rank));
                    break;
                }
            }
            for (int8_t i = source.file + 1; i < 8; i++) {
                Piece square = this->chessboard.get_piece(Coordinate(i, destination.rank));
                if (square.piece_type == PieceType.Rook && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, destination.rank));
                    break;
                }
            }
            for (int8_t j = source.rank - 1; j >= 0; j--) {
                Piece square = this->chessboard.get_piece(Coordinate(destination.file, j));
                if (square.piece_type == PieceType.Rook && square.color == this->color) {
                    potential_sources.push_back(Coordinate(destination.file, j));
                    break;
                }
            }
            for (int8_t j = source.rank + 1; j < 8; j++) {
                Piece square = this->chessboard.get_piece(Coordinate(destination.file, j));
                if (square.piece_type == PieceType.Rook && square.color == this->color) {
                    potential_sources.push_back(Coordinate(destination.file, j));
                    break;
                }
            }
            break;
        case PieceType.Knight:
            std::vector<Coordinate> potential_knight_sources;
            potential_knight_sources.push_back(Coordinate(destination.file + 2, destination.rank + 1));
            potential_knight_sources.push_back(Coordinate(destination.file + 1, destination.rank + 2));
            potential_knight_sources.push_back(Coordinate(destination.file - 1, destination.rank + 2));
            potential_knight_sources.push_back(Coordinate(destination.file - 2, destination.rank + 1));
            potential_knight_sources.push_back(Coordinate(destination.file - 2, destination.rank - 1));
            potential_knight_sources.push_back(Coordinate(destination.file - 1, destination.rank - 2));
            potential_knight_sources.push_back(Coordinate(destination.file + 1, destination.rank - 2));
            potential_knight_sources.push_back(Coordinate(destination.file + 2, destination.rank - 1));

            std::vector<Coordinate>::iterator it = potential_knight_sources.begin();

            for (it; it != potential_knight_sources.end(); it++) {
                Piece square = this->chessboard.get_piece(*it);
                if (square.piece_type == PieceType.Knight && square.color == this->color) {
                    potential_sources.push_back(*it);
                }
            }
            break;

        case PieceType.Bishop:
            for (int8_t i = source.file + 1, j = source.rank + 1; i < 8 && j < 8; i++, j++) {
                Piece square = this->chessboard.get_piece(Coordinate(i, j));
                if (square.piece_type == PieceType.Bishop && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, j));
                }
            }
            for (int8_t i = source.file - 1, j = source.rank + 1; i >= 0 && j < 8; i--, j++) {
                Piece square = this->chessboard.get_piece(Coordinate(i, j));
                if (square.piece_type == PieceType.Bishop && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, j));
                }
            }
            for (int8_t i = source.file - 1, j = source.rank - 1; i >= 0 && j >= 0; i--, j--) {
                Piece square = this->chessboard.get_piece(Coordinate(i, j));
                if (square.piece_type == PieceType.Bishop && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, j));
                }
            }
            for (int8_t i = source.file + 1, j = source.rank - 1; i < 8 && j >= 0; i++, j--) {
                Piece square = this->chessboard.get_piece(Coordinate(i, j));
                if (square.piece_type == PieceType.Bishop && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, j));
                }
            }

        case PieceType.Queen:
            // horizontal and vertical
            for (int8_t i = source.file - 1; i >= 0; i--) {
                Piece square = this->chessboard.get_piece(Coordinate(i, destination.rank));
                if (square.piece_type == PieceType.Queen && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, destination.rank));
                    break;
                }
            }
            for (int8_t i = source.file + 1; i < 8; i++) {
                Piece square = this->chessboard.get_piece(Coordinate(i, destination.rank));
                if (square.piece_type == PieceType.Queen && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, destination.rank));
                    break;
                }
            }
            for (int8_t j = source.rank - 1; j >= 0; j--) {
                Piece square = this->chessboard.get_piece(Coordinate(destination.file, j));
                if (square.piece_type == PieceType.Queen && square.color == this->color) {
                    potential_sources.push_back(Coordinate(destination.file, j));
                    break;
                }
            }
            for (int8_t j = source.rank + 1; j < 8; j++) {
                Piece square = this->chessboard.get_piece(Coordinate(destination.file, j));
                if (square.piece_type == PieceType.Queen && square.color == this->color) {
                    potential_sources.push_back(Coordinate(destination.file, j));
                    break;
                }
            }

            // diagonal
            for (int8_t i = source.file + 1, j = source.rank + 1; i < 8 && j < 8; i++, j++) {
                Piece square = this->chessboard.get_piece(Coordinate(i, j));
                if (square.piece_type == PieceType.Queen && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, j));
                }
            }
            for (int8_t i = source.file - 1, j = source.rank + 1; i >= 0 && j < 8; i--, j++) {
                Piece square = this->chessboard.get_piece(Coordinate(i, j));
                if (square.piece_type == PieceType.Queen && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, j));
                }
            }
            for (int8_t i = source.file - 1, j = source.rank - 1; i >= 0 && j >= 0; i--, j--) {
                Piece square = this->chessboard.get_piece(Coordinate(i, j));
                if (square.piece_type == PieceType.Queen && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, j));
                }
            }
            for (int8_t i = source.file + 1, j = source.rank - 1; i < 8 && j >= 0; i++, j--) {
                Piece square = this->chessboard.get_piece(Coordinate(i, j));
                if (square.piece_type == PieceType.Queen && square.color == this->color) {
                    potential_sources.push_back(Coordinate(i, j));
                }
            }
            break;

        case PieceType.King:
            std::vector<Coordinate> potential_king_sources;
            potential_king_sources.push_back(Coordinate(destination.file + 1, destination.rank + 1));
            potential_king_sources.push_back(Coordinate(destination.file, destination.rank + 1));
            potential_king_sources.push_back(Coordinate(destination.file - 1, destination.rank + 1));
            potential_king_sources.push_back(Coordinate(destination.file - 1, destination.rank));
            potential_king_sources.push_back(Coordinate(destination.file - 1, destination.rank - 1));
            potential_king_sources.push_back(Coordinate(destination.file, destination.rank - 1));
            potential_king_sources.push_back(Coordinate(destination.file + 1, destination.rank - 1));
            potential_king_sources.push_back(Coordinate(destination.file + 1, destination.rank));

            std::vector<Coordinate>::iterator it = potential_king_sources.begin();

            for (it; it != potential_king_sources.end(); it++) {
                Piece square = this->chessboard.get_piece(*it);
                if (square.piece_type == PieceType.King && square.color == this->color) {
                    potential_sources.push_back(*it);
                }
            }
            break;
            
    }
}