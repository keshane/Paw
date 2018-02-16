package com.keshane.Paw;

interface Logic {
    void makeMove(Move.Builder move, Move.History moveHistory, Board board) throws
            NoSuchMoveException, AmbiguousNotationException;
}
