#include <functional>
#include <cstdint>
/**
 * Defines the different type of pieces
 */
enum class PieceType
{
    None = 0,
    Pawn = 1,
    Rook = 2,
    Knight = 3,
    Bishop = 4,
    Queen = 5,
    King = 6,
};

namespace std {
template <>
struct hash<PieceType>
{
    size_t operator()(const PieceType &p) const;
};
}

/**
 * Defines the color of a component of the game
 */
enum class Color
{
    None,
    Black,
    White
};
namespace std
{
template <>
struct hash<Color>
{
    size_t operator()(const Color &c) const;
};
}
/**
 * Defines the non-exclusive categories of moves that can be made.
 */
enum class MoveType : std::uint8_t
{
    None = 0,
    Normal = 1,
    Capture = 1 << 1,
    En_Passant = 1 << 2,
    Queenside_Castle = 1 << 3,
    Kingside_Castle = 1 << 4,
    Check = 1 << 5,
    Checkmate = 1 << 6,

};

// TODO also create |= and &= operator definitions
MoveType operator| (MoveType a, MoveType b);
MoveType operator& (MoveType a, MoveType b);



