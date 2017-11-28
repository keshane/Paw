#include "utility.h"
namespace std
{
size_t hash<PieceType>::operator()(const PieceType &p) const
{
    return (hash<int>()(static_cast<int>(p)));
}

size_t hash<Color>::operator()(const Color &c) const
{
    return (hash<int>()(static_cast<int>(c)));
}
}

MoveType operator&(MoveType a, MoveType b)
{
    return static_cast<MoveType>(static_cast<std::uint8_t>(a) & static_cast<std::uint8_t>(b));
}

MoveType operator|(MoveType a, MoveType b)
{
    return static_cast<MoveType>(static_cast<std::uint8_t>(a) | static_cast<std::uint8_t>(b));
}

void debug_out(const char function_name[], const char message[])
{
    std::cout << function_name << ": " << message << std::endl;
}

void debug_out(const char function_name[], std::string message)
{
    std::cout << function_name << ": " << message << std::endl;
}
