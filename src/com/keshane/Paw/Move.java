package com.keshane.Paw;

import java.util.ArrayList;
import java.util.EnumSet;
import java.util.Iterator;
import java.util.List;

/**
 * A Move object contains all the information necessary to define a chess move.
 * A Move is immutable, so it should be created using the {@link Move.Builder}.
 */
final class Move {
    final int destinationFile;
    final int destinationRank;

    final int sourceFile;
    final int sourceRank;

    final Color player;

    final EnumSet<Type> types;

    final Piece.Type pieceType;

    final Piece.Type promotionPieceType;

    /**
     * Create an immutable Move object from the Builder.
     * @param builder
     */
    private Move(Builder builder) {
        this.destinationRank = builder.getDestinationRank();
        this.destinationFile = builder.getDestinationFile();
        this.sourceRank = builder.getSourceRank();
        this.sourceFile = builder.getSourceFile();
        this.player = builder.player;
        this.types = builder.getTypes();
        this.pieceType = builder.getPieceType();
        this.promotionPieceType = builder.promotionPieceType;
    }

    Board.Coordinate getDestination() {
        return new Board.Coordinate(destinationFile, destinationRank);
    }

    Board.Coordinate getSource() {
        return new Board.Coordinate(sourceFile, sourceRank);
    }


    EnumSet<Type> getTypes() {
        return EnumSet.copyOf(this.types);
    }

    Color getPlayer() {
        return player;
    }

    @Override
    public String toString() {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(pieceType.getNotation());
        stringBuilder.append((char)('a' + sourceFile));
        stringBuilder.append((char)('1' + sourceRank));
        stringBuilder.append((char)('a' + destinationFile));
        stringBuilder.append((char)('1' + destinationRank));

        return stringBuilder.toString();
    }

    Piece.Type getPieceType() {
        return pieceType;
    }

    enum Type {
        NORMAL,
        KINGSIDE_CASTLE,
        QUEENSIDE_CASTLE,
        CAPTURE,
        EN_PASSANT,
        PROMOTION,
        CHECK,
        CHECKMATE
    }

    /**
     * The setter methods of this class should be used to build a {@link Move} object.
     */
    static final class Builder {
        private int destinationFile = -1;
        private int destinationRank = -1;
        private int sourceFile = -1;
        private int sourceRank = -1;
        private Color player;
        private EnumSet<Type> types;
        private Piece.Type pieceType;
        Piece.Type promotionPieceType;

        // TODO validate setters

        /**
         * Initiate the builder
         */
        Builder() {
            this.types = EnumSet.noneOf(Type.class);
        }

        Builder(Builder oldbuiler) {
            this.destinationFile = oldbuiler.destinationFile;
            this.destinationRank = oldbuiler.destinationRank;
            this.sourceFile = oldbuiler.sourceFile;
            this.sourceRank = oldbuiler.sourceRank;
            this.player = oldbuiler.player;
            this.types = oldbuiler.types.clone();
            this.pieceType = oldbuiler.pieceType;
            this.promotionPieceType = oldbuiler.promotionPieceType;
        }

        /**
         * Sets the {@code destinationFile} and returns a reference to this Builder so that the methods can be chained together.
         *
         * @param destinationFile the {@code destinationFile} to set
         * @return a reference to this Builder
         */
        Builder setDestinationFile(int destinationFile) {
            if (!isInRange(destinationFile)) {
                throw new IllegalArgumentException("Destination file is not in range.");
            }
            this.destinationFile = destinationFile;
            return this;
        }

        /**
         * Sets the {@code destinationRank} and returns a reference to this Builder so that the methods can be chained together.
         *
         * @param destinationRank the {@code destinationRank} to set
         * @return a reference to this Builder
         */
        Builder setDestinationRank(int destinationRank) {
            if (!isInRange(destinationRank)) {
                throw new IllegalArgumentException("Destination rank is not in range.");
            }
            this.destinationRank = destinationRank;
            return this;
        }

        /**
         * Sets the {@code sourceFile} and returns a reference to this Builder so that the methods can be chained together.
         *
         * @param sourceFile the {@code sourceFile} to set
         * @return a reference to this Builder
         */
        Builder setSourceFile(int sourceFile) {
            if (!isInRange(sourceFile)) {
                throw new IllegalArgumentException("Source file is not in range.");
            }
            this.sourceFile = sourceFile;
            return this;
        }

        /**
         * Sets the {@code sourceRank} and returns a reference to this Builder so that the methods can be chained together.
         *
         * @param sourceRank the {@code sourceRank} to set
         * @return a reference to this Builder
         */
        Builder setSourceRank(int sourceRank) {
            if (!isInRange(sourceRank)) {
                throw new IllegalArgumentException("Source rank is not in range.");
            }
            this.sourceRank = sourceRank;
            return this;
        }

        /**
         * Sets the {@code player} and returns a reference to this Builder so that the methods can be chained together.
         *
         * @param player the {@code player} to set
         * @return a reference to this Builder
         */
        Builder setPlayer(Color player) {
            this.player = player;
            return this;
        }

        /**
         * Sets the {@code types} and returns a reference to this Builder so that the methods can be chained together.
         *
         * @param type the {@code type} to set
         * @return a reference to this Builder
         */
        Builder addType(Type type) {
            this.getTypes().add(type);
            return this;
        }

        /**
         * Sets the {@code pieceType} and returns a reference to this Builder so that the methods can be chained together.
         *
         * @param pieceType the {@code pieceType} to set
         * @return a reference to this Builder
         */
        public Builder setPieceType(Piece.Type pieceType) {
            this.pieceType = pieceType;
            return this;
        }

        private boolean isInRange(int coordinate) {
            return coordinate >= 0 && coordinate < 8;
        }

        /**
         * Returns a {@code Move} built from the parameters previously set.
         *
         * @return a {@code Move} built with parameters of this {@code Move.Builder}
         */
        public Move build() {
            return new Move(this);
        }

        Builder setDestination(Board.Coordinate destination) {
            destinationFile = destination.file;
            destinationRank = destination.rank;
            return this;
        }

        Builder setPromotionPieceType(Piece.Type pieceType) {
            this.promotionPieceType = pieceType;
            return this;
        }

        Board.Coordinate getDestination() {
            return new Board.Coordinate(destinationFile, destinationRank);
        }

        Builder setSource(Board.Coordinate source) {
            sourceFile = source.file;
            sourceRank = source.rank;
            return this;
        }

        Board.Coordinate getSource() {
            return new Board.Coordinate(sourceFile, sourceRank);
        }

        int getDestinationFile() {
            return destinationFile;
        }

        int getDestinationRank() {
            return destinationRank;
        }

        int getSourceFile() {
            return sourceFile;
        }

        int getSourceRank() {
            return sourceRank;
        }

        Color getPlayer() {
            return player;
        }

        EnumSet<Type> getTypes() {
            return types;
        }

        Piece.Type getPieceType() {
            return pieceType;
        }
    }

    final static class History {
        private final List<Move> history;

        History() {
            history = new ArrayList<>();
        }

        void add(Move move) {
            if (move.getPlayer() == Color.WHITE) {
                if (history.size() == 0 || history.get(history.size() - 1).player == Color.BLACK) {
                    history.add(move);
                }
                else {
                    throw new UnsupportedOperationException("Cannot add a move by white because " +
                            "it doesn't follow a move by black");
                }
            }
            else {
                if (history.size() > 0 && history.get(history.size() - 1).player == Color.WHITE) {
                    history.add(move);
                }
                else {
                    throw new UnsupportedOperationException("Cannot add a move by black because " +
                            "it doesn't follow a move by white");
                }
            }
        }

        List<Move> getHistory() {
            return new ArrayList<>(history);
        }

        Move peekLast() {
            if (history.size() > 0) {
                return history.get(history.size() - 1);
            }
            else {
                return null;
            }
        }

        int getFullMoveNumber() {
            return (history.size() + 1) / 2;
        }

        int getHalfMoveNumber() {
            return history.size();
        }

        @Override
        public String toString() {
            StringBuilder stringBuilder = new StringBuilder();
            Iterator<Move> iterator = history.iterator();

            for (int moveNumber = 1; moveNumber <= getFullMoveNumber(); moveNumber++) {
                stringBuilder.append(moveNumber);
                stringBuilder.append(". ");
                stringBuilder.append(String.format("%1$-9s",iterator.next().toString()));
                if (iterator.hasNext()) {
                    stringBuilder.append(iterator.next().toString());
                }

                stringBuilder.append("\n");
            }

            return stringBuilder.toString();

        }

    }
}
