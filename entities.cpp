#include "entities.h"

bool operator==(Piece a, Piece b)
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

std::ostream &operator<<(std::ostream &output, const Move &move)
{
    static const std::string PieceTypeNames[] =
        {
            "None",
            "Pawn",
            "Rook",
            "Knight",
            "Bishop",
            "Queen",
            "King"};
    output << "Source file:"
           << std::to_string(move.source.file)
           << "\nSource rank:"
           << std::to_string(move.source.rank)
           << "\nDestination file:"
           << std::to_string((char)move.destination.file)
           << "\nDestination rank:"
           << std::to_string((char)move.destination.rank)
            << "\nPiece type:"
            << std::to_string(static_cast<int>(move.piece_type))
           << "\nMove type:"
           << std::to_string(static_cast<int>(move.move_type));

    return output;
}

namespace std
{
size_t hash<Piece>::operator()(const Piece &p) const
{
    return (hash<PieceType>()(p.piece_type) ^ hash<Color>()(p.color));
}
}