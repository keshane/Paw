#include <iostream>
#include "utility.h"

/**
 * Utility struct to pack rank and file into one type
 */
typedef struct
{
    int file;
    int rank;
} Coordinate;

/**
 * Defines a specific piece by its type and color
 */
typedef struct
{
    PieceType piece_type;
    Color color;
} Piece;

bool operator==(Piece a, Piece b);
namespace std {
template <>
struct hash<Piece>
{
    size_t operator()(const Piece &p) const;
};
}

/**
 * Represents a square on the chessboard.
 */
typedef struct
{
    bool occupied;
    Piece piece;
} Square;

/**
 * Represents a single chess move.
 */
typedef struct Move
{
    Coordinate source;
    Coordinate destination;

    PieceType piece_type;
    MoveType move_type;

} Move;

std::ostream& operator<< (std::ostream& output, const Move& move);
