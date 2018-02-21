package com.keshane.Paw;

import java.text.ParseException;

public class Game {
    private Move.History moveHistory;

    private Board board;

    private Player whitePlayer;
    private Player blackPlayer;

    private Color currentTurn;

    private Move.History history;

    Game(String whiteName, String blackName) {
        board = new Board(Board.Configuration.NORMAL);
        whitePlayer = new Player(whiteName, Color.WHITE, new Player.WhiteStandardLogic());
        blackPlayer = new Player(blackName, Color.BLACK, new Player.BlackStandardLogic());
        currentTurn = Color.WHITE;
        history = new Move.History();
    }

    void makeMove(String notation) throws ParseException, NoSuchMoveException,
            AmbiguousNotationException, KingInCheckException {
        Move move;
        if (currentTurn == Color.WHITE) {
            move = whitePlayer.makeMove(notation, history, board);
            currentTurn = Color.BLACK;
        }
        else {
            move = blackPlayer.makeMove(notation, history, board);
            currentTurn = Color.WHITE;
        }

        history.add(move);
    }

    void printBoard() {
        System.out.println("BLACK: " + blackPlayer.getName());
        System.out.println(board.toString());
        System.out.println("WHITE: " + whitePlayer.getName());
    }

    void printHistory() {
        System.out.println(history.toString());
    }



}
