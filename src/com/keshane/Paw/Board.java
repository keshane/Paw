package com.keshane.Paw;

import java.util.HashSet;
import java.util.Set;

/**
 * This class represents a chessboard and the pieces on that chessboard.
 */
public class Board {
    /**
     * The data structure that represents the board and the pieces it may contain
     */
    private Piece[][] board;

    /**
     * The number of files in the board
     */
    private final int FILES = 8;

    /**
     * The number of ranks in the board
     */
    private final int RANKS = 8;

    /**
     * Construct the board based on the configuration.
     *
     * @param configuration indicates the initial arrangement of the pieces
     */
    Board(Configuration configuration) {
        board = new Piece[FILES][RANKS];
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
        else if (configuration == Configuration.TEST) {
            board[0][6] = new Piece(Piece.Type.PAWN, Color.WHITE);
            board[0][1] = new Piece(Piece.Type.PAWN, Color.BLACK);

            board[1][5] = new Piece(Piece.Type.KING, Color.WHITE);
            board[1][2] = new Piece(Piece.Type.KING, Color.BLACK);
        }
    }

    /**
     * A copy constructor.
     *
     * Use this to create a copy of another board.
     *
     * @param oldBoard the Board to create a copy of.
     */
    Board(Board oldBoard) {
        board = new Piece[FILES][RANKS];
        for (int file = 0; file < FILES; file++) {
            for (int rank = 0; rank < RANKS; rank++) {
                Piece piece = oldBoard.getPiece(file, rank);
                if (null != piece) {
                    board[file][rank] = new Piece(piece);
                }
                else {
                    board[file][rank] = null;
                }
            }
        }

    }

    /**
     * Removes the piece at the specified location
     *
     * @param location a location on the board that has a piece on it
     * @return the piece that was removed
     */
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

        board[location.file][location.rank] = null;

        return piece;
    }

    /**
     * Places the piece at the specified location on the board
     *
     * @param piece       the piece to be placed
     * @param destination the location at which to put the piece
     */
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

        board[destination.file][destination.rank] = piece;
    }

    private boolean isLocationInRange(Board.Coordinate location) {
        return location.file >= 0 && location.file < FILES && location.rank >= 0 && location.rank
                < RANKS;
    }

    /**
     * Gets the piece at the specified file and rank.
     *
     * @param file the column that the piece is in
     * @param rank the row that the piece is in
     * @return a Piece object or null if there is no piece at the location
     */
    Piece getPiece(int file, int rank) {
        if (file < 0 || file >= FILES || rank < 0 || rank >= RANKS) {
            throw new IllegalArgumentException("Coordinate is not in range 0 to 7: (" + file + "," +
                    rank + ")");
        }
        return board[file][rank];
    }

    /**
     * Gets the piece at the specified location.
     *
     * @param location the position of the piece
     * @return a Piece object or null if there is no piece at the location
     */
    Piece getPiece(Board.Coordinate location) {
        return getPiece(location.file, location.rank);
    }

    /**
     * Finds all the pieces of the specified type and color
     *
     * @param pieceType the piece type of the piece to search for
     * @param color     the color of the piece to search for
     * @return a Set containing the locations of all pieces that fulfill the piece type and color
     * criteria
     */
    Set<Coordinate> getLocationsOfPiece(Piece.Type pieceType, Color color) {
        Set<Coordinate> locations = new HashSet<>();
        for (int file = 0; file < FILES; file++) {
            for (int rank = 0; rank < RANKS; rank++) {
                Piece piece = getPiece(file, rank);
                if (null != piece && piece.getPieceType() == pieceType && piece.getColor() ==
                        color) {
                    locations.add(new Coordinate(file, rank));
                }
            }
        }

        return locations;
    }


    /**
     * Creates a human-readable representation of the board.
     *
     * @return a String formatted to look like a board
     */
    @Override
    public String toString() {
        return toStringWhite();
    }

    String toString(Color color) {
        // TODO extract common lines into one method
        if (color == Color.WHITE) {
            return toStringWhite();
        }
        else {
            return toStringBlack();
        }
    }

    String toStringWhite() {
        // TODO clean up unicode characters
        StringBuilder boardVisual = new StringBuilder();

        // top of board
        boardVisual.append(" \u250C");
        for (int file = 0; file < FILES - 1; file++) {
            boardVisual.append("\u2500\u2500\u2500\u252C");
        }
        boardVisual.append("\u2500\u2500\u2500\u2510\n");

        for (int rank = RANKS - 1; rank >= 0; rank--) {
            // rank coordinates
            boardVisual.append(rank + 1);
            for (int file = 0; file < FILES; file++) {
                boardVisual.append("\u2502");
                Piece piece = getPiece(file, rank);

                String squareFillCharacter = (file + rank) % 2 == 0 ? "." : " ";
                boardVisual.append(squareFillCharacter);

                if (piece == null) {
                    boardVisual.append(squareFillCharacter);
                }
                else {
                    boardVisual.append(piece.toString());
                }

                boardVisual.append(squareFillCharacter);
            }

            boardVisual.append("\u2502\n");

            if (rank > 0) {
                boardVisual.append(" \u251C");
                for (int file = 0; file < FILES - 1; file++) {
                    boardVisual.append("\u2500\u2500\u2500\u253C");
                }
                boardVisual.append("\u2500\u2500\u2500\u2524\n");
            }
        }

        // bottom of board
        boardVisual.append(" \u2514");
        for (int file = 0; file < FILES - 1; file++) {
            boardVisual.append("\u2500\u2500\u2500\u2534");
        }
        boardVisual.append("\u2500\u2500\u2500\u2518\n");

        // file coordinates
        for (int file = 0; file < FILES; file++) {
            boardVisual.append("   ");
            boardVisual.append(String.valueOf((char) (file + 'a')));
        }
        boardVisual.append("\n");

        return boardVisual.toString();
    }

    /**
     * Creates a human-readable representation of the board from black's perspective.
     *
     * @return a String formatted to look like a board
     */

    String toStringBlack() {
        StringBuilder boardVisual = new StringBuilder();

        // top of board
        boardVisual.append(" \u250C");
        for (int file = FILES - 1; file > 0; file--) {
            boardVisual.append("\u2500\u2500\u2500\u252C");
        }
        boardVisual.append("\u2500\u2500\u2500\u2510\n");

        for (int rank = 0; rank < RANKS; rank++) {
            // rank coordinates
            boardVisual.append(rank + 1);
            for (int file = FILES - 1; file >= 0; file--) {
                boardVisual.append("\u2502");
                Piece piece = getPiece(file, rank);

                String squareFillCharacter = (file + rank) % 2 == 0 ? "." : " ";
                boardVisual.append(squareFillCharacter);

                if (piece == null) {
                    boardVisual.append(squareFillCharacter);
                }
                else {
                    boardVisual.append(piece.toString());
                }

                boardVisual.append(squareFillCharacter);
            }

            boardVisual.append("\u2502\n");

            if (rank < RANKS - 1) {
                boardVisual.append(" \u251C");
                for (int file = FILES - 1; file > 0; file--) {
                    boardVisual.append("\u2500\u2500\u2500\u253C");
                }
                boardVisual.append("\u2500\u2500\u2500\u2524\n");
            }
        }

        // bottom of board
        boardVisual.append(" \u2514");
        for (int file = FILES - 1; file > 0; file--) {
            boardVisual.append("\u2500\u2500\u2500\u2534");
        }
        boardVisual.append("\u2500\u2500\u2500\u2518\n");

        // file coordinates
        for (int file = 0; file < FILES; file++) {
            boardVisual.append("   ");
            boardVisual.append(String.valueOf((char) ('h' - file)));
        }
        boardVisual.append("\n");

        return boardVisual.toString();
    }

    /**
     * An entity object used to represent a location on a {@link Board}.
     */
    static class Coordinate {
        /**
         * The file (0-based) of the location.
         */
        final int file;
        /**
         * The rank (0-based) of the location.
         */
        final int rank;

        /**
         * Construct a Coordinate object
         *
         * @param file the column of the location to represent
         * @param rank the row of the location to represent
         */
        Coordinate(int file, int rank) {
            this.file = file;
            this.rank = rank;
        }

        /**
         * Determines whether the location represented by this Coordinate is the same location
         * represented by another Coordinate.
         *
         * @param second the other Coordinate to compare to
         * @return true if the other Coordinate is equal to this Coordinate, else false
         */
        @Override
        public boolean equals(Object second) {
            if (second == null) {
                return false;
            }
            if (!(second instanceof Board.Coordinate)) {
                return false;
            }

            Board.Coordinate secondCoordinate = (Board.Coordinate) second;

            return this.file == secondCoordinate.file && this.rank == secondCoordinate.rank;
        }

        /**
         * Creates a human-readable representation of this Coordinate
         *
         * @return a String describing this location
         */
        @Override
        public String toString() {
            return "(" + file + ", " + rank + ")";
        }
    }

    /**
     * Represents possible initial placement of pieces on a board.
     */
    enum Configuration {
        EMPTY, // no pieces
        NORMAL, // standard chess setup
        TEST, // used for setting up pieces to quickly test this code
    }
}
