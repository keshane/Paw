#include <iostream>
#include "../chess_gui.h"

int main(int argc, char *argv[])
{
    std::string notation;

    std::cout << "Enter a move\n";
    while (getline(std::cin, notation))
    {
        Move parsed_move = Parser::parse_algebraic_notation(notation);
        std::cout << parsed_move << std::endl;
        std::cout << "Enter a move\n";
    }
}
