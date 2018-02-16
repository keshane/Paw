package com.keshane.Paw;

import java.util.EnumMap;
import java.util.Map;

class Piece {
    enum Type {
        PAWN(""),
        ROOK("R"),
        KNIGHT("N"),
        BISHOP("B"),
        QUEEN("Q"),
        KING("K");
        private final String notation;

        Type(String notation) {
            this.notation = notation;
        }

        String getNotation() {
            return notation;
        }

        static Type parse(String notation) {
            for (Type pieceType : Type.values()) {
                if (pieceType.getNotation().equals(notation)) {
                    return pieceType;
                }
            }

            throw new IllegalArgumentException("Notation does not represent a piece.");
        }
    }

    private static Map<Color, Map<Type, String>> stringRepresentations = new EnumMap<>(Color.class);

    static {
        Map<Type, String> whiteRepresentations = new EnumMap<>(Type.class);
        whiteRepresentations.put(Type.KING, "\u2654");
        whiteRepresentations.put(Type.QUEEN, "\u2655");
        whiteRepresentations.put(Type.ROOK, "\u2656");
        whiteRepresentations.put(Type.BISHOP, "\u2657");
        whiteRepresentations.put(Type.KNIGHT, "\u2658");
        whiteRepresentations.put(Type.PAWN, "\u2659");

        stringRepresentations.put(Color.WHITE, whiteRepresentations);

        Map<Type, String> blackRepresentations = new EnumMap<>(Type.class);
        blackRepresentations.put(Type.KING, "\u265A");
        blackRepresentations.put(Type.QUEEN, "\u265B");
        blackRepresentations.put(Type.ROOK, "\u265C");
        blackRepresentations.put(Type.BISHOP, "\u265D");
        blackRepresentations.put(Type.KNIGHT, "\u265E");
        blackRepresentations.put(Type.PAWN, "\u265F");

        stringRepresentations.put(Color.BLACK, blackRepresentations);

    }



    private final Type pieceType;
    private final Color color;
    private final String representation;

    Piece(Type pieceType, Color color) {
        this.pieceType = pieceType;
        this.color = color;
        representation = stringRepresentations.get(color).get(pieceType);
    }


    Color getColor() {
        return this.color;
    }

    Type getPieceType() {
        return this.pieceType;
    }

    @Override
    public String toString() {
        return representation;
    }


}
