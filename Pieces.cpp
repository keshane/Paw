#include <cstdint>
#include <iostream>
#include <locale>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include "chess_gui.h"


/* Pawn methods */
Pawn::Pawn(Coordinate location) {
    _location = location;
}

Coordinate Pawn::get_location() {
    return _location;
}

void Pawn::set_location(Coordinate location) {
    _location = location;
}

std::vector<Coordinate> Pawn::get_possible_moves() {
}

/* Bishop methods */
Bishop::Bishop(Coordinate location) {
    _location = location;
}

Coordinate Bishop::get_location() {
    return _location;
}

void Bishop::set_location(Coordinate location) {
    _location = location;
    possible_moves = calculate_possible_moves();
}

std::vector<Coordinate> Bishop::calculate_possible_moves() {
    for (int i = _location.i; i < 8; i++) {
        for (int j = _location.j; j < 8 j++) {
            _possible_moves.push_back(new Coordinate(i, j));
        }

        for (int j = _location.j; j >= 0 j++) {
            _possible_moves.push_back(new Coordinate(i, j));
        }
    }

    for (int i = _location.i; i >= 8; i++) {
        for (int j = _location.j; j < 8 j++) {
            _possible_moves.push_back(new Coordinate(i, j));
        }

        for (int j = _location.j; j >= 0 j++) {
            _possible_moves.push_back(new Coordinate(i, j));
        }
    }
}
            





