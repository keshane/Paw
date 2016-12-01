#include <string>
#include <iostream>
#include "chess_gui.h"

int main(int argc, char *argv[]) {
    Board board;
    board.print_board();
    std::string move;
    while(getline(std::cin, move)) {
        if (move.empty() || move == "\n")
            continue;
        if (move == "exit")
            break;
        if (board.enter_move(move))
            board.print_board();
    }
    std::cout << "Thank you for playing today\n";
}
