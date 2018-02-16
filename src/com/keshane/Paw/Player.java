package com.keshane.Paw;

import java.text.ParseException;
import java.util.HashSet;
import java.util.Set;

class Player {
    private final String name;
    private final Color color;
    private final Logic variantLogic;

    Player(String name, Color color) {
        this.name = name;
        this.color = color;
        this.variantLogic = new Player.StandardLogic(color); // TODO

    }

    String getName() {
        return this.name;
    }

    Logic getVariantLogic() {
        return variantLogic;
    }

    void makeMove(String notation, Move.History moveHistory, Board board) throws ParseException,
            NoSuchMoveException, AmbiguousNotationException {
        Parser notationParser = new Parser(notation);
        Move.Builder move = notationParser.getMove();
        variantLogic.makeMove(move, moveHistory, board);
        // TODO
    }

    static class StandardLogic implements Logic {
        private final Color color;

        private StandardLogic(Color color) {
            this.color = color;
        }

        @Override
        public void makeMove(Move.Builder partialMove, Move.History moveHistory, Board board)
        throws NoSuchMoveException, AmbiguousNotationException {
            Move fullMove = buildMove(partialMove, board);
            executeMove(fullMove, board);
        }

        private void executeMove(Move move, Board board) {
            if (move.getTypes().contains(Move.Type.NORMAL)) {
                Piece piece = board.removePiece(new Board.Coordinate(move.getSourceFile(), move
                        .getSourceRank()));
                board.placePiece(piece, new Board.Coordinate(move.getDestinationFile(), move
                        .getDestinationRank()));
            }
        }

        private Move buildMove(Move.Builder partialMove, Board board) throws NoSuchMoveException,
                AmbiguousNotationException {
            if (partialMove.getSourceFile() < 0 && partialMove.getSourceRank() < 0) {
                Board.Coordinate source = findSourceSquare(partialMove, board);
                partialMove.setSourceFile(source.file());
                partialMove.setSourceRank(source.rank());
            }

            return partialMove.build();
        }

        private Board.Coordinate findSourceSquare(Move.Builder partialMove, Board board) throws
                NoSuchMoveException, AmbiguousNotationException{
            Set<Board.Coordinate> locationsOfPieceType = board.getLocationsOfPiece(partialMove
                    .getPieceType(), color);

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
            if (possibleSourceSquares.size() > 1) {
                // ambiguous notation
                 throw new AmbiguousNotationException("Ambiguous notation - multiple pieces " +
                         partialMove.getPieceType().toString() + " can reach the destination " +
                         "square");
                // check for possibility of check
            }

            return possibleSourceSquares.iterator().next();
        }

        private boolean isValidKingMove(Board.Coordinate source, Board.Coordinate
                destination, Board board) {
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


        private boolean isValidPawnMove(Board.Coordinate coordinate,
                                        Board
                                                board) {
            return false;
        }

        private boolean isValidMove(Move.Builder partialMove, Board.Coordinate source, Board
                board) {
            Board.Coordinate destination = new Board.Coordinate(partialMove.getDestinationFile(),
                    partialMove.getDestinationRank());

            if (partialMove.getTypes().contains(Move.Type.CAPTURE)) {
                if (board.getPiece(destination) == null || board.getPiece(destination).getColor().opposite()
                        != color) {
                    return false;
                }
            }
            boolean isValid = false;
            switch (partialMove.getPieceType()) {
                case KING:
                    isValid = isValidKingMove(source, destination, board);
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
                    isValid = isValidPawnMove(source, board);
                    break;
                default:
                    break;
            }

            return isValid;
        }

        private boolean isClearPath(Board.Coordinate source, Board.Coordinate destination, Board
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
}
