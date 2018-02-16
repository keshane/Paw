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
        whitePlayer = new Player(whiteName, Color.WHITE);
        blackPlayer = new Player(blackName, Color.BLACK);
        currentTurn = Color.WHITE;
        history = new Move.History();
    }

    void makeMove(String notation) throws ParseException, NoSuchMoveException, AmbiguousNotationException {
        if (currentTurn == Color.WHITE) {
            whitePlayer.makeMove(notation, history, board);
            currentTurn = Color.BLACK;
        }
        else {
            blackPlayer.makeMove(notation, history, board);
            currentTurn = Color.WHITE;
        }
    }

    void printBoard() {
        System.out.println("BLACK: " + blackPlayer.getName());
        System.out.println(board.toString());
        System.out.println("WHITE: " + whitePlayer.getName());
    }



}
