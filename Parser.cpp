#include <string>
#include "chess_gui.h"

Parser() {}

Move Parser::parse_algebraic_notation(std::string notation)
{
    this->move_notation = notation;

    // TODO create fresh move
    this->parsed_move = new Move();

    if (this->move_notation == "O-O" || this->move_notation == "0-0-0")
    {
        // castle king side
    }
    else if (this->move_notation == "O-O-O" || this->move_notation == "0-0-0")
    {
        // castle queen side
    }
    else if (this->move_notation /* ends in e.p. */)
    {
        // en passant
    }
    else if (this->move_notation /* ends in B, N, R, or Q */)
    {
        // promotion
    }
    else if (this->move_notation.back() == "+")
    {
        this->move_notation.pop_back();
        parse_normal_move();
        this->parsed_move.check |= MoveType.Check;
        return this->parsed_move;
    }
    else if (this->move_notation.back() == "#")
    {
        this->move_notation.pop_back();
        parse_normal_move();
        this->parsed_move.checkmate |= MoveType.Checkmate;
        return this->parsed_move;
    }
    else
    {
        return parse_normal_move();
    }
}

void Parser::parse_normal_move()
{
    if (this->move_notation.back() >= '1' && this->move_notation.back() <= '8') {
        parse_destination_rank();
    }
    else {
        // throw
    }
}

void Parser::parse_destination_rank() {
    this->parsed_move.destination.rank = this->move_notation.back() - '1';

    this->move_notation.pop_back();
    if (this->move_notation.back() >= 'a' && this->move_notation.back() <= 'h') {
        parse_destination_file();
    }
    else {
        // throw
    }
}

void Parser::parse_destination_file() {
    this->parsed_move.destination.file = this->move_notation.back() - 'a';

    this->move_notation.pop_back();
    if (this->move_notation.empty()       ||
        this->move_notation.back() == 'K' ||
        this->move_notation.back() == 'Q' ||
        this->move_notation.back() == 'R' ||
        this->move_notation.back() == 'B' ||
        this->move_notation.back() == 'N') {
        parse_moving_piece();
    }
    else if (this->move_notation.back() == 'x' || this->move_notation.back() == 'X') {
        parse_capture();
    }
    else if (this->move_notation.back() >= 'a' && this->move_notation.back() <= 'h') {
        parse_source_file();
    }
    else if (this->move_notation.back() >= '1' && this->move_notation.back() <= '8') {
        parse_source_rank();
    }
    else {
        // throw
    }
}

void Parser::parse_capture(){
    this->parsed_move.move_type |= MoveType.Capture;

    this->move_notation.pop_back();
    if (this->move_notation.back() == 'K' ||
        this->move_notation.back() == 'Q' ||
        this->move_notation.back() == 'R' ||
        this->move_notation.back() == 'B' ||
        this->move_notation.back() == 'N') {

        parse_moving_piece();
    }
    else if (this->move_notation.back() >= 'a' && this->move_notation.back() <= 'h') {
        parse_source_file();
    }
    else if (this->move_notation.back() >= '1' && this->move_notation.back() <= '8') {
        parse_source_rank();
    }
    else {
        // throw
    }
}

void Parser::parse_source_rank(){
    this->parsed_move.source.rank = this->move_notation.back() - '1';

    this->move_notation.pop_back()
    if (this->move_notation.back() == 'K' ||
        this->move_notation.back() == 'Q' ||
        this->move_notation.back() == 'R' ||
        this->move_notation.back() == 'B' ||
        this->move_notation.back() == 'N') {

        parse_moving_piece();
    }
    else if (this->move_notation.back() >= 'a' && this->move_notation.back() <= 'h') {
        parse_source_file();
    }
    else {
        // throw
    }
}
void Parser::parse_source_file(){
    this->parsed_move.source.file = this->move_notation.back() - 'a';

    this->move_notation.pop_back();
    if (this->move_notation.empty() ||
        this->move_notation.back() == 'K' ||
        this->move_notation.back() == 'Q' ||
        this->move_notation.back() == 'R' ||
        this->move_notation.back() == 'B' ||
        this->move_notation.back() == 'N') {

        parse_moving_piece();
    }
    else {
        // throw
    }
    
}

void Parser::parse_moving_piece(){
    const std::unordered_map<std::string, Piece> piece_from_notation = {
        {"K", Piece.King},
        {"Q", Piece.Queen},
        {"B", Piece.Bishop},
        {"N", Piece.Knight},
        {"R", Piece.Rook}
    };

    if (this->move_notation.empty()) {
        this->parsed_move.piece = Piece.Pawn;
    }
    else {
        this->parsed_move.piece = piece_from_notation[this->move_notation.back()];
    }


    this->parsed_move.pop_back();
    if (!this->move_notation.empty()) {
        // throw

    }

}
