#include "chess_gui.h"

Game::Game(std::string white_name, std::string black_name) 
    : this.chessboard(), this.white_player(white_name), this.black_player(black_name), this.white_move(true) {
}

Game::enter_move(std::string move) {
    bool successful;
    if (this.white_move) {
        successful = this.white_player.make_move(move);
    }
    else {
        successful = this.black_player.make_move(move);
    }

    // TODO store moves here
    return successful;

}