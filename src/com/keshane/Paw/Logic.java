package com.keshane.Paw;

interface Logic {
    Move makeMove(Move.Builder move, Move.History moveHistory, Board board) throws
            NoSuchMoveException, AmbiguousNotationException, KingInCheckException;
}
