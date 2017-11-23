#include "chess_gui.h"

Game::Game(std::string white_name, std::string black_name) 
    : _white_player(white_name, _chessboard, Color::White),
      _black_player(black_name, _chessboard, Color::Black),
      _white_move(true)
   {

   }

bool Game::enter_move(std::string move) {
    bool successful;
    if (_white_move) {
        _white_player.make_move(move);
    }
    else {
        _black_player.make_move(move);
    }

    // TODO store moves here
    return true;

}

void Game::print_board()
{
    _chessboard.print_board();
}