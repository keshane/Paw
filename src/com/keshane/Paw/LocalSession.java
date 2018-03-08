package com.keshane.Paw;

import java.text.ParseException;
import java.util.Scanner;

class LocalSession implements Session {
    private final Board.Configuration configuration;

    LocalSession(Board.Configuration configuration) {
        this.configuration = configuration;
    }

    @Override
    public void runGame() {
        Scanner localIn = new Scanner(System.in);
        System.out.println("Enter name of player for white:");
        String whitePlayer = localIn.nextLine();

        System.out.println("Enter name of player for black:");
        String blackPlayer = localIn.nextLine();

        Game game = new Game(whitePlayer, blackPlayer, configuration);

        Color currentTurn = Color.WHITE;
        game.printBoard(currentTurn);
        while (true) {
            try {
                System.out.println("Enter move or '?' to view options:");
                String move = localIn.nextLine();
                if (move.equalsIgnoreCase("?")) {
                    System.out.println("\t'q' or 'quit' terminates the program");
                    System.out.println("\t'history' displays the move history");
                    continue;
                }
                else if (move.equalsIgnoreCase("q") || move.equalsIgnoreCase("quit")) {
                    System.out.println("Quitting...");
                    break;
                }
                else if (move.equalsIgnoreCase("history")) {
                    game.printHistory();
                    continue;
                }

                game.makeMove(move);
                currentTurn = game.getCurrentTurn();
                game.printBoard(currentTurn);
            } catch (ParseException exception) {
                System.out.println("Invalid move: " + exception.getMessage());
                System.out.println("\t at position " + exception.getErrorOffset());
                System.out.println("Please try again.");
            } catch (NoSuchMoveException | AmbiguousNotationException | KingInCheckException exception) {
                System.out.println(exception.getMessage());
            }

        }

        localIn.close();
    }
}
