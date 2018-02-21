package com.keshane.Paw;

import java.text.ParseException;
import java.util.EnumSet;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

class Player {
    private final String name;
    private final Color color;
    private final Logic variantLogic;

    Player(String name, Color color, Logic variantLogic) {
        this.name = name;
        this.color = color;
        this.variantLogic = variantLogic; // TODO

    }

    String getName() {
        return this.name;
    }

    Logic getVariantLogic() {
        return variantLogic;
    }

    Move makeMove(String notation, Move.History moveHistory, Board board) throws ParseException,
            NoSuchMoveException, AmbiguousNotationException, KingInCheckException {
        Parser notationParser = new Parser(notation);
        Move.Builder move = notationParser.getMove();
        move.setPlayer(color);
        Move executedMove = variantLogic.makeMove(move, moveHistory, board);
        return executedMove;
        // TODO
    }

    static abstract class StandardLogic implements Logic {
        private final Color color;

        private StandardLogic(Color color) {
            this.color = color;
        }

        @Override
        public Move makeMove(Move.Builder partialMove, Move.History moveHistory, Board board)
                throws NoSuchMoveException, AmbiguousNotationException, KingInCheckException {
            Move fullMove = buildMove(partialMove, moveHistory, board);

            // check for checks
            Board verificationBoard = new Board(board);
            executeMove(fullMove, verificationBoard);
            if (isKingInCheck(verificationBoard)) {
                throw new KingInCheckException("Cannot make this move because the king is in " +
                        "check");
            }

            executeMove(fullMove, board);

            return fullMove;
        }


        private void executeMove(Move move, Board board) {
            EnumSet<Move.Type> moveTypes = move.getTypes();
            if (moveTypes.contains(Move.Type.NORMAL)) {
                Piece piece = board.removePiece(move.getSource());
                if (moveTypes.contains(Move.Type.CAPTURE)) {
                    board.removePiece(move.getDestination());
                }
                board.placePiece(piece, move.getDestination());
            }
            else if (moveTypes.contains(Move.Type.KINGSIDE_CASTLE)) {
                // TODO
                executeKingsideCastle(board);
            }
            else if (moveTypes.contains(Move.Type.QUEENSIDE_CASTLE)) {
                executeQueensideCastle(board);
            }
        }

        private Move buildMove(Move.Builder partialMove, Move.History moveHistory, Board board)
                throws NoSuchMoveException,
                AmbiguousNotationException {
            EnumSet<Move.Type> moveTypes = partialMove.getTypes();

            if (moveTypes.contains(Move.Type.NORMAL)) {
                Board.Coordinate source = findSourceSquare(partialMove, board);
                partialMove.setSourceFile(source.file());
                partialMove.setSourceRank(source.rank());
            }
            else if (moveTypes.contains(Move.Type.KINGSIDE_CASTLE)) {
                boolean isValid = isValidKingsideCastle(partialMove, moveHistory, board);
                if (!isValid) {
                    throw new NoSuchMoveException("Cannot castle kingside because there are " +
                            "pieces in the way or because the king or rook has moved already.");
                }
            }
            else if (moveTypes.contains(Move.Type.QUEENSIDE_CASTLE)) {
                boolean isValid = isValidQueensideCastle(partialMove, moveHistory, board);
                if (!isValid) {
                    throw new NoSuchMoveException("Cannot castle queenside because there are " +
                            "pieces in the way or because the king or rook has moved already.");
                }
            }

            return partialMove.build();
        }

        protected abstract void executeKingsideCastle(Board board);

        protected abstract void executeQueensideCastle(Board board);

        protected abstract boolean isValidKingsideCastle(Move.Builder partialMove, Move
                .History moveHistory, Board board);

        protected abstract boolean isValidQueensideCastle(Move.Builder partialMove, Move
                .History moveHistory, Board board);

        private Board.Coordinate findSourceSquare(Move.Builder partialMove, Board board) throws
                NoSuchMoveException, AmbiguousNotationException {
            Set<Board.Coordinate> locationsOfPieceType = board.getLocationsOfPiece(partialMove
                    .getPieceType(), partialMove.getPlayer());

            Set<Board.Coordinate> possibleSourceSquares = new HashSet<>();
            for (Board.Coordinate source : locationsOfPieceType) {
                if (isValidMove(partialMove, source, board)) {
                    possibleSourceSquares.add(source);
                }
            }


            if (possibleSourceSquares.size() == 0) {
                // no possible moves
                throw new NoSuchMoveException("Piece " + partialMove.getPieceType().toString
                        () + " cannot reach the destination square.");
            }

            // Narrow down the possible sources by comparing them to the specified source file or
            // source rank from the move input
            Set<Board.Coordinate> filteredSourceSquares = possibleSourceSquares;
            int expectedSourceFile = partialMove.getSourceFile();
            if (expectedSourceFile > 0) {
                filteredSourceSquares = filteredSourceSquares.stream().filter(coordinate -> coordinate
                        .file() == expectedSourceFile).collect(Collectors.toSet());
            }

            int expectedSourceRank = partialMove.getSourceRank();
            if (expectedSourceRank > 0) {
                filteredSourceSquares = filteredSourceSquares.stream().filter(coordinate ->
                        coordinate.rank() == expectedSourceRank).collect(Collectors.toSet());
            }

            if (filteredSourceSquares.size() > 1) {
                // ambiguous notation
                throw new AmbiguousNotationException("Ambiguous notation - multiple pieces " +
                        partialMove.getPieceType().toString() + " can reach the destination " +
                        "square");
                // check for possibility of check
            }

            if (filteredSourceSquares.size() == 0) {
                // no possible moves
                throw new NoSuchMoveException("Piece " + partialMove.getPieceType().toString
                        () + "  on specified file o rank cannot reach the destination square.");
            }
            return filteredSourceSquares.iterator().next();
        }

        private boolean isValidKingMove(Board.Coordinate source, Board.Coordinate
                destination) {
            int fileDistance = Math.abs(destination.file() - source.file());
            int rankDistance = Math.abs(destination.rank() - source.rank());

            return (fileDistance | rankDistance) == 1;
        }

        private boolean isValidQueenMove(Board.Coordinate source, Board.Coordinate destination, Board
                board) {
            return isValidBishopMove(source, destination, board) || isValidRookMove(source,
                    destination, board);
        }

        private boolean isValidRookMove(Board.Coordinate source, Board.Coordinate destination, Board
                board) {
            boolean isSameFile = (source.file() == destination.file());
            boolean isSameRank = (source.rank() == destination.rank());

            return (isSameFile || isSameRank) && isClearPath(source, destination, board);
        }


        private boolean isValidBishopMove(Board.Coordinate source, Board.Coordinate destination,
                                          Board board) {
            int fileDistance = Math.abs(destination.file() - source.file());
            int rankDistance = Math.abs(destination.rank() - source.rank());
            boolean isDiagonal = (fileDistance == rankDistance);

            return isDiagonal && isClearPath(source, destination, board);

        }

        private boolean isValidKnightMove(Board.Coordinate source, Board.Coordinate destination,
                                          Board board) {
            int fileDistance = Math.abs(destination.file() - source.file());
            int rankDistance = Math.abs(destination.rank() - source.rank());

            return (fileDistance != 0 && rankDistance != 0) && (fileDistance + rankDistance == 3);
        }


        protected abstract boolean isValidPawnMove(Board.Coordinate source, Board.Coordinate
                destination, Board board);

        private boolean isValidMove(Move.Builder partialMove, Board.Coordinate source, Board
                board) {
            Board.Coordinate destination = new Board.Coordinate(partialMove.getDestinationFile(),
                    partialMove.getDestinationRank());

            if (partialMove.getTypes().contains(Move.Type.CAPTURE)) {
                if (board.getPiece(destination) == null || board.getPiece(destination).getColor().opposite()
                        != partialMove.getPlayer()) {
                    return false;
                }
            }
            else if (partialMove.getTypes().contains(Move.Type.NORMAL)) {
                if (board.getPiece(destination) != null) {
                    return false;
                }
            }
            boolean isValid = false;
            switch (partialMove.getPieceType()) {
                case KING:
                    isValid = isValidKingMove(source, destination);
                    break;
                case QUEEN:
                    isValid = isValidQueenMove(source, destination, board);
                    break;
                case ROOK:
                    isValid = isValidRookMove(source, destination, board);
                    break;
                case KNIGHT:
                    isValid = isValidKnightMove(source, destination, board);
                    break;
                case BISHOP:
                    isValid = isValidBishopMove(source, destination, board);
                    break;
                case PAWN:
                    isValid = isValidPawnMove(source, destination, board);
                    break;
                default:
                    break;
            }


            return isValid;
        }

        protected boolean isClearPath(Board.Coordinate source, Board.Coordinate destination, Board
                board) {
            int fileDifference = destination.file() - source.file();
            int rankDifference = destination.rank() - source.rank();

            int fileDirection = fileDifference == 0 ? 0 : fileDifference / Math.abs(fileDifference);
            int rankDirection = rankDifference == 0 ? 0 : rankDifference / Math.abs(rankDifference);

            int filePath = source.file() + fileDirection;
            int rankPath = source.rank() + rankDirection;

            while (!(filePath == destination.file() && rankPath == destination.rank())) {
                if (board.getPiece(filePath, rankPath) == null) {
                    filePath += fileDirection;
                    rankPath += rankDirection;
                }
                else {
                    return false;
                }

            }

            return true;
        }

        protected boolean hasPieceMoved(Board.Coordinate source, Move.History history) {
            List<Move> historyList = history.getHistory();

            boolean hasMoved = historyList.stream().filter(move -> move.getSource().equals
                    (source)).collect(Collectors.toList()).size() > 0;

            return hasMoved;

        }

        protected boolean isValidCastle(Move.History moveHistory, Board
                board, Board.Coordinate kingStart, Board.Coordinate rookStart) {
            return isClearPath(kingStart, rookStart, board) && !hasPieceMoved(kingStart,
                    moveHistory) && !hasPieceMoved(rookStart, moveHistory);
        }

        private boolean isKingInCheck(Board board) {
            Set<Board.Coordinate> kingLocations = board.getLocationsOfPiece(Piece.Type.KING, color);
            Board.Coordinate kingLocation = kingLocations.iterator().next();

            Set<Board.Coordinate> attackingPieceLocations = new HashSet<>();
            for (int file = 0; file < 8; file++) {
                for (int rank = 0; rank < 8; rank++) {
                    Piece piece = board.getPiece(file, rank);
                    if (null != piece && piece.getColor() == color.opposite() && piece
                            .getPieceType() != Piece.Type.KING) {
                        attackingPieceLocations.add(new Board.Coordinate(file, rank));
                    }
                }
            }

            Move.Builder captureKingMove = new Move.Builder().setDestination(kingLocation)
                    .addType(Move.Type.CAPTURE).addType(Move.Type.NORMAL).setPlayer(color.opposite());

            for (Board.Coordinate attackingPieceLocation : attackingPieceLocations) {
                captureKingMove.setPieceType(board.getPiece(attackingPieceLocation).getPieceType());
                if (isValidMove(captureKingMove, attackingPieceLocation, board)) {
                    return true;
                }
            }

            return false;
        }


    }

    static class WhiteStandardLogic extends StandardLogic {
        private static Board.Coordinate kingStart = new Board.Coordinate(4, 0);
        private static Board.Coordinate kingRookStart = new Board.Coordinate(7, 0);
        private static Board.Coordinate queenRookStart = new Board.Coordinate(0, 0);

        private static Board.Coordinate kingsideCastledKingLocation = new Board.Coordinate(6, 0);
        private static Board.Coordinate queensideCastledKingLocation = new Board.Coordinate(2, 0);
        private static Board.Coordinate castledKingRookLocation = new Board.Coordinate(5, 0);
        private static Board.Coordinate castledQueenRookLocation = new Board.Coordinate(3, 0);

        WhiteStandardLogic() {
            super(Color.WHITE);
        }

        @Override
        protected boolean isValidPawnMove(Board.Coordinate source, Board.Coordinate destination,
                                          Board board) {
            boolean isValid = false;
            if (destination.file() == source.file()) {
                if (destination.rank() - source.rank() == 1) {
                    isValid = true;
                }

                if (source.rank() == 1 && destination.rank() - source.rank() == 2 && isClearPath
                        (source, destination,
                                board)) {
                    isValid = true;

                }

            }

            return isValid;
        }

        @Override
        protected boolean isValidKingsideCastle(Move.Builder partialMove, Move.History
                moveHistory, Board board) {
            return super.isValidCastle(moveHistory, board, WhiteStandardLogic.kingStart,
                    WhiteStandardLogic.kingRookStart);
        }

        @Override
        protected boolean isValidQueensideCastle(Move.Builder partialMove, Move.History
                moveHistory, Board board) {
            return super.isValidCastle(moveHistory, board, WhiteStandardLogic.kingStart,
                    WhiteStandardLogic.queenRookStart);
        }

        @Override
        protected void executeKingsideCastle(Board board) {
            Piece king = board.removePiece(WhiteStandardLogic.kingStart);
            Piece rook = board.removePiece(WhiteStandardLogic.kingRookStart);

            board.placePiece(king, WhiteStandardLogic.kingsideCastledKingLocation);
            board.placePiece(rook, WhiteStandardLogic.castledKingRookLocation);
        }

        @Override
        protected void executeQueensideCastle(Board board) {
            Piece king = board.removePiece(WhiteStandardLogic.kingStart);
            Piece rook = board.removePiece(WhiteStandardLogic.kingRookStart);

            board.placePiece(king, WhiteStandardLogic.queensideCastledKingLocation);
            board.placePiece(rook, WhiteStandardLogic.castledQueenRookLocation);
        }
    }

    static class BlackStandardLogic extends StandardLogic {
        private static Board.Coordinate kingStart = new Board.Coordinate(4, 7);
        private static Board.Coordinate kingRookStart = new Board.Coordinate(7, 7);
        private static Board.Coordinate queenRookStart = new Board.Coordinate(0, 7);

        private static Board.Coordinate kingsideCastledKingLocation = new Board.Coordinate(6, 7);
        private static Board.Coordinate queensideCastledKingLocation = new Board.Coordinate(2, 7);
        private static Board.Coordinate castledKingRookLocation = new Board.Coordinate(5, 7);
        private static Board.Coordinate castledQueenRookLocation = new Board.Coordinate(3, 7);

        BlackStandardLogic() {
            super(Color.BLACK);
        }

        @Override
        protected boolean isValidPawnMove(Board.Coordinate source, Board.Coordinate destination,
                                          Board board) {
            boolean isValid = false;
            if (destination.file() == source.file()) {
                if (destination.rank() - source.rank() == -1) {
                    isValid = true;
                }

                if (source.rank() == 6 && destination.rank() - source.rank() == -2 && isClearPath
                        (source, destination,
                                board)) {
                    isValid = true;

                }

            }

            return isValid;
        }

        @Override
        protected boolean isValidKingsideCastle(Move.Builder partialMove, Move.History moveHistory,
                                                Board board) {
            return super.isValidCastle(moveHistory, board, BlackStandardLogic.kingStart,
                    BlackStandardLogic.kingRookStart);
        }

        @Override
        protected boolean isValidQueensideCastle(Move.Builder partialMove, Move.History
                moveHistory, Board board) {
            return super.isValidCastle(moveHistory, board, BlackStandardLogic.kingStart,
                    BlackStandardLogic.queenRookStart);
        }

        @Override
        protected void executeKingsideCastle(Board board) {
            Piece king = board.removePiece(BlackStandardLogic.kingStart);
            Piece rook = board.removePiece(BlackStandardLogic.kingRookStart);

            board.placePiece(king, BlackStandardLogic.kingsideCastledKingLocation);
            board.placePiece(rook, BlackStandardLogic.castledKingRookLocation);
        }

        @Override
        protected void executeQueensideCastle(Board board) {
            Piece king = board.removePiece(BlackStandardLogic.kingStart);
            Piece rook = board.removePiece(BlackStandardLogic.queenRookStart);

            board.placePiece(king, BlackStandardLogic.queensideCastledKingLocation);
            board.placePiece(rook, BlackStandardLogic.castledQueenRookLocation);
        }
    }
}
