package com.keshane.Paw;

import java.text.ParseException;
import java.time.Instant;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.println("Enter name of player for white:");
        String whitePlayer = in.nextLine();

        System.out.println("Enter name of player for black:");
        String blackPlayer = in.nextLine();

        Game game = new Game(whitePlayer, blackPlayer);

        while(true) {
            try {
                game.printBoard();
                System.out.println("Enter move ('q' or 'quit' to exit):");
                String move = in.nextLine();
                if (move.equalsIgnoreCase("q") || move.equalsIgnoreCase("quit")) {
                    System.out.println("Quitting...");
                    break;
                }
                else if (move.equalsIgnoreCase("history")) {
                    game.printHistory();
                    continue;
                }
                game.makeMove(move);
            }
            catch (ParseException exception) {
                System.out.println("Invalid move: " + exception.getMessage());
                System.out.println("\t at position " + exception.getErrorOffset());
                System.out.println("Please try again.");
            }
            catch (NoSuchMoveException | AmbiguousNotationException exception) {
                System.out.println(exception.getMessage());
            }

        }
    }
}
