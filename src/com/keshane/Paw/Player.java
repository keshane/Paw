package com.keshane.Paw;

import java.text.ParseException;
import java.util.EnumSet;
import java.util.HashSet;
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
            NoSuchMoveException, AmbiguousNotationException {
        Parser notationParser = new Parser(notation);
        Move.Builder move = notationParser.getMove();
        move.setPlayer(color);
        Move executedMove = variantLogic.makeMove(move, moveHistory, board);
        return executedMove;
        // TODO
    }

    static abstract class StandardLogic implements Logic {
        private StandardLogic() {
        }

        @Override
        public Move makeMove(Move.Builder partialMove, Move.History moveHistory, Board board)
                throws NoSuchMoveException, AmbiguousNotationException {
            Move fullMove = buildMove(partialMove, board);
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
            }
        }

        private Move buildMove(Move.Builder partialMove, Board board) throws NoSuchMoveException,
                AmbiguousNotationException {
            Board.Coordinate source = findSourceSquare(partialMove, board);
            partialMove.setSourceFile(source.file());
            partialMove.setSourceRank(source.rank());

            return partialMove.build();
        }

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
            int expectedSourceFile = partialMove.getSourceFile();
            int expectedSourceRank = partialMove.getSourceRank();

            Set<Board.Coordinate> filteredSourceSquares = possibleSourceSquares;
            if (expectedSourceFile > 0) {
                filteredSourceSquares = filteredSourceSquares.stream().filter(coordinate -> coordinate
                        .file() == expectedSourceFile).collect(Collectors.toSet());
            }

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
            return isValidBishopMove(source, destination, board) && isValidRookMove(source,
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
                if (board.getPiece(filePath, rankPath) != null) {
                    return false;
                }
                filePath += fileDirection;
                rankPath += rankDirection;
            }

            return true;
        }
    }

    static class WhiteStandardLogic extends StandardLogic {
        WhiteStandardLogic() {
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
    }

    static class BlackStandardLogic extends StandardLogic {
        BlackStandardLogic() {
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
    }
}
