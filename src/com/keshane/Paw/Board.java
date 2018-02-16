package com.keshane.Paw;

import java.util.HashSet;
import java.util.Set;

public class Board {
    private Piece[][] board;


    Board(Configuration configuration) {
        board = new Piece[8][8];
        // set up the normal initial chessboard configuration
        if (configuration == Configuration.NORMAL) {
            // set up white pieces
            board[0][0] = new Piece(Piece.Type.ROOK, Color.WHITE);
            board[1][0] = new Piece(Piece.Type.KNIGHT, Color.WHITE);
            board[2][0] = new Piece(Piece.Type.BISHOP, Color.WHITE);
            board[3][0] = new Piece(Piece.Type.QUEEN, Color.WHITE);
            board[4][0] = new Piece(Piece.Type.KING, Color.WHITE);
            board[5][0] = new Piece(Piece.Type.BISHOP, Color.WHITE);
            board[6][0] = new Piece(Piece.Type.KNIGHT, Color.WHITE);
            board[7][0] = new Piece(Piece.Type.ROOK, Color.WHITE);

            for (int file = 0; file < 8; file++) {
                board[file][1] = new Piece(Piece.Type.PAWN, Color.WHITE);
            }

            // set up black pieces
            board[0][7] = new Piece(Piece.Type.ROOK, Color.BLACK);
            board[1][7] = new Piece(Piece.Type.KNIGHT, Color.BLACK);
            board[2][7] = new Piece(Piece.Type.BISHOP, Color.BLACK);
            board[3][7] = new Piece(Piece.Type.QUEEN, Color.BLACK);
            board[4][7] = new Piece(Piece.Type.KING, Color.BLACK);
            board[5][7] = new Piece(Piece.Type.BISHOP, Color.BLACK);
            board[6][7] = new Piece(Piece.Type.KNIGHT, Color.BLACK);
            board[7][7] = new Piece(Piece.Type.ROOK, Color.BLACK);

            for (int file = 0; file < 8; file++) {
                board[file][6] = new Piece(Piece.Type.PAWN, Color.BLACK);
            }
        }
    }

    Piece removePiece(Board.Coordinate location) {
        if (!isLocationInRange(location)) {
            throw new IllegalArgumentException("Location " + location.toString() + " is out of " +
                    "range of the board.");
        }

        Piece piece = getPiece(location);

        if (piece == null) {
            throw new IllegalArgumentException("Location at " + location.toString() + " does not " +
                    "contain a piece");
        }

        board[location.file()][location.rank()] = null;

        return piece;
    }
    void placePiece(Piece piece, Board.Coordinate destination) {
                if (!isLocationInRange(destination)) {
            throw new IllegalArgumentException("Destination " + destination.toString() + " is not" +
                    " in the range of the board");
        }
        if (getPiece(destination) != null) {
            throw new IllegalArgumentException("Location at " + destination.toString() + " " +
                    "already contains a piece");
        }

        if (piece == null) {
            throw new IllegalArgumentException("Cannot place a null piece");
        }

        board[destination.file()][destination.rank()] = piece;
    }

    private boolean isLocationInRange(Board.Coordinate location) {
        if (location.file() >= 0 && location.file() <= 7 && location.rank() >= 0 && location.file
                () <= 7) {
            return true;
        }
        else {
            return false;
        }
    }

    Piece getPiece(int file, int rank) {
        if (file < 0 || file > 7 || rank < 0 || rank > 7) {
            throw new IllegalArgumentException("Coordinate is not in range 0 to 7: (" + file + "," +
                    rank + ")");
        }
        return board[file][rank];
    }

    Piece getPiece(Board.Coordinate location) {
        return getPiece(location.file(), location.rank());
    }

    Set<Coordinate> getLocationsOfPiece(Piece.Type pieceType, Color color) {
        Set<Coordinate> locations = new HashSet<>();
        for (int file = 0; file < 8; file++) {
            for (int rank = 0; rank < 8; rank++) {
                Piece piece = getPiece(file, rank);
                if (null != piece && piece.getPieceType() == pieceType && piece.getColor() ==
                        color) {
                    locations.add(new Coordinate(file, rank));
                }
            }
        }

        return locations;
    }

    @Override
    public String toString() {
        StringBuilder boardVisual = new StringBuilder();

        // top of board
        boardVisual.append("\u250C");
        for (int file = 0; file < 7; file++) {
            boardVisual.append("\u2500\u2500\u2500\u252C");
        }
        boardVisual.append("\u2500\u2500\u2500\u2510\n");

        for (int rank = 7; rank >= 0; rank --) {
            for (int file = 0; file <= 7; file++) {
                boardVisual.append("\u2502");
                Piece piece = getPiece(file, rank);
                boardVisual.append(" ");
                if (piece == null) {
                    boardVisual.append(" ");
                }
                else {
                    boardVisual.append(piece.toString());
                }

                boardVisual.append(" ");
            }

            boardVisual.append("\u2502\n");

            if (rank > 0) {
                boardVisual.append("\u251C");
                for (int file = 0; file < 7; file++) {
                    boardVisual.append("\u2500\u2500\u2500\u253C");
                }
                boardVisual.append("\u2500\u2500\u2500\u2524\n");
            }
        }

        // bottom of board
        boardVisual.append("\u2514");
        for (int file = 0; file < 7; file++) {
            boardVisual.append("\u2500\u2500\u2500\u2534");
        }
        boardVisual.append("\u2500\u2500\u2500\u2518\n");

        return boardVisual.toString();
    }

    static class Coordinate {
        private final int file;
        private final int rank;
        Coordinate(int file, int rank)
        {
            this.file = file;
            this.rank = rank;
        }

        int file() {
            return file;
        }

        int rank() {
            return rank;
        }

        @Override
        public String toString() {
            return "(" + file + ", " + rank + ")";
        }
    }

    enum Configuration {
        EMPTY,
        NORMAL
    }
}
