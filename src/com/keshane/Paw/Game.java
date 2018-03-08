package com.keshane.Paw;

import java.text.ParseException;

public class Game {
    private final Board board;

    private final Player whitePlayer;
    private final Player blackPlayer;

    private Color currentTurn;

    private final Move.History history;

    Game(String whiteName, String blackName, Board.Configuration configuration) {
        board = new Board(configuration);
        whitePlayer = new Player(whiteName, Color.WHITE, new Player.WhiteStandardLogic());
        blackPlayer = new Player(blackName, Color.BLACK, new Player.BlackStandardLogic());
        currentTurn = Color.WHITE;
        history = new Move.History();
    }

    public void makeMove(String notation) throws ParseException, NoSuchMoveException,
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

    public void printBoard(Color perspective) {
        System.out.println(board.toString(perspective));
    }

    public void printHistory() {
        System.out.println(history.toString());
    }

    public Color getCurrentTurn() {
        return currentTurn;
    }



}
