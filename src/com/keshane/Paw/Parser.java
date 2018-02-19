package com.keshane.Paw;

import java.text.ParseException;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

class Parser {
    private static final String KINGSIDE_CASTLE_OHS = "O-O";
    private static final String KINGSIDE_CASTLE_ZEROES = "0-0";
    private static final String QUEENSIDE_CASTLE_OHS = "O-O-O";
    private static final String QUEENSIDE_CASTLE_ZEROES = "0-0-0";
    private static final String EN_PASSANT = "ep";

    private static final String[] pieceNotations = new String[]{Piece.Type.BISHOP.getNotation(),
            Piece.Type.KNIGHT.getNotation(), Piece.Type.ROOK.getNotation(), Piece.Type.QUEEN
            .getNotation(), Piece.Type.KING.getNotation()};
    private static final Set<String> PIECE_NOTATIONS = new HashSet<>(Arrays.asList
            (pieceNotations));
    private String notation;
    private Move.Builder move;

    Parser(String notation) throws ParseException {
        this.notation = notation;
        this.move = new Move.Builder();
        parseFullNotation(this.notation);
    }

    String getNotation() {
        return this.notation;
    }

    Move.Builder getMove() {
        return this.move;
    }

    // TODO consider using StringBuilder
    private void parseFullNotation(String notation) throws ParseException {

        // First, parse away unnecessary information
        if (notation.endsWith("+")) {
            move.addType(Move.Type.CHECK);
            notation = notation.substring(0, notation.length() - 1);
        }
        else if (notation.endsWith("#")) {
            move.addType(Move.Type.CHECKMATE);
            notation = notation.substring(0, notation.length() - 1);
        }

        if (notation.equalsIgnoreCase(Parser.KINGSIDE_CASTLE_OHS) || notation.equalsIgnoreCase(KINGSIDE_CASTLE_ZEROES)) {
            move.addType(Move.Type.KINGSIDE_CASTLE);
            return;
        }
        else if (notation.equalsIgnoreCase(Parser.QUEENSIDE_CASTLE_OHS) || notation.equalsIgnoreCase(Parser.QUEENSIDE_CASTLE_ZEROES)) {
            move.addType(Move.Type.QUEENSIDE_CASTLE);
            return;
        }
        else if (notation.endsWith(Parser.EN_PASSANT)) {
            move.addType(Move.Type.EN_PASSANT);
            notation = notation.substring(0, notation.length() - 1);
        }
        else if (notation.endsWith(Piece.Type.QUEEN.getNotation()) ||
                notation.endsWith(Piece.Type.BISHOP.getNotation()) ||
                notation.endsWith(Piece.Type.KNIGHT.getNotation()) ||
                notation.endsWith(Piece.Type.ROOK.getNotation())) {
            move.addType(Move.Type.PROMOTION);
            notation = notation.substring(0, notation.length() - 1);
        }
        else {
            move.addType(Move.Type.NORMAL);
        }

        if (notation.length() < 2) {
            throw new ParseException("Notation isn't long enough.", notation.length() - 1);
        }
        // start parsing the notation from the last character and moving toward the front
        parseDestinationRank(notation.substring(0, notation.length()));
    }

    /**
     * Parses the last character of {@code notation} as the rank of the destination square.
     *
     * @param notation the move notation whose last character is the destination rank
     */
    private void parseDestinationRank(String notation) throws ParseException {
        int destinationRank = notation.charAt(notation.length() - 1) - '1';

        if (destinationRank < 0 || destinationRank > 7) {
            throw new ParseException("Destination rank is not between '1' and '8'.", notation
                    .length() - 1);
        }

        move.setDestinationRank(destinationRank);
        parseDestinationFile(notation.substring(0, notation.length() - 1));
    }

    private void parseDestinationFile(String notation) throws ParseException {
        int destinationFile = notation.charAt(notation.length() - 1) - 'a';

        if (destinationFile < 0 || destinationFile > 7) {
            throw new ParseException("Destination file is not between 'a' and 'h'.", notation
                    .length() - 1);
        }

        move.setDestinationFile(destinationFile);
        parseLastSymbol(notation.substring(0, notation.length() - 1));
    }

    private void parseLastSymbol(String notation) throws ParseException {
        if (notation.length() == 0) {
            move.setPieceType(Piece.Type.PAWN);
            return;
        }
        char symbol = notation.charAt(notation.length() - 1);
        if ('x' == symbol) {
            parseCapture(notation);
        }
        else if (symbol >= 'a' && symbol <= 'h') {
            parseSourceFile(notation);
        }
        else if (symbol >= '1' && symbol <= '8') {
            parseSourceRank(notation);
        }
        else if (Parser.PIECE_NOTATIONS.contains(String.valueOf(symbol))) {
            parsePiece(notation);
        }
        else {
            throw new ParseException("Unrecognized symbol", notation.length() - 1);
        }
    }

    private void parseCapture(String notation) throws ParseException {
        move.addType(Move.Type.CAPTURE);

        parseLastSymbol(notation.substring(0, notation.length() - 1));
    }

    private void parseSourceFile(String notation) throws ParseException {
        int sourceFile = notation.charAt(notation.length() - 1) - 'a';

        if (sourceFile < 0 || sourceFile > 7) {
            throw new ParseException("Source file is not between 'a' and 'h'.", notation
                    .length() - 1);
        }
        move.setSourceFile(sourceFile);
        parseLastSymbol(notation.substring(0, notation.length() - 1));
    }

    private void parseSourceRank(String notation) throws ParseException {
        int sourceRank = notation.charAt(notation.length() - 1) - '1';

        if (sourceRank < 0 || sourceRank > 7) {
            throw new ParseException("Source rank is not between '1' and '8'.", notation
                    .length() - 1);
        }
        move.setSourceRank(sourceRank);
        parseLastSymbol(notation.substring(0, notation.length() - 1));
    }

    private void parsePiece(String notation) throws ParseException {
        char pieceNotation = notation.charAt(notation.length() - 1);

        move.setPieceType(Piece.Type.parse(String.valueOf(pieceNotation)));

        if (notation.length() != 1) {
            throw new ParseException("Unexpected additional symbols before piece notation.",
                    notation.length());
        }

    }


}



