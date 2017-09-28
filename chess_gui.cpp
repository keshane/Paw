#include <string>
#include <iostream>
#include "chess_gui.h"
void DIE(char const *message) {
    std::cout << message << std::endl;
}

int main(int argc, char *argv[]) {
    std::string white_name;
    std::string black_name;

    std::cout << "Enter name for white player\n";
    getline(std::cin, white_name);

    std::cout << "Enter name for black player\n";
    getline(std::cin, black_name);

    Game game(white_name, black_name);
    game.print_board();
    std::string move;
    while(getline(std::cin, move)) {
        if (move.empty() || move == "\n")
            continue;
        if (move == "exit")
            break;
        if (game.enter_move(move)) {
            game.print_board();
        }
    }



    std::cout << "Thank you for playing today\n";
}
