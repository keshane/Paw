package com.keshane.Paw;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.text.ParseException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class RemoteSession implements Session {
    private Map<Color, String> promptMessages;

    private final Color color;
    private final Map<Color, String> names;
    private final Map<Color, Scanner> inReaders;
    private final PrintWriter remoteOut;

    RemoteSession(Color color, InputStream inputStream, OutputStream outputStream) {
        this.color = color;

        // associate the input streams with the appropriate player color
        inReaders = new HashMap<>();
        inReaders.put(color.opposite(), new Scanner(inputStream));
        inReaders.put(color, new Scanner(System.in));

        remoteOut = new PrintWriter(outputStream, true);
        names = new HashMap<>();
    }

    private void exchangeNames() {
        System.out.println("Enter your name: ");
        String thisName = inReaders.get(color).nextLine();
        names.put(color, thisName);
        remoteOut.println(thisName);
        System.out.println("Waiting on other player to enter name...");

        Scanner remoteIn = inReaders.get(color.opposite());
        String otherName = remoteIn.nextLine();
        names.put(color.opposite(), otherName);

        System.out.println(names.get(color.opposite()) + " successfully connected!");

        promptMessages = new HashMap<>();
        promptMessages.put(color, "Enter move or '?' to view options:");
        promptMessages.put(color.opposite(), "Waiting on " + names.get(color.opposite()) + " to " +
                "make a move...");
    }

    @Override
    public void runGame() {
        exchangeNames();
        Game game = new Game(names.get(Color.WHITE), names.get(Color.BLACK), Board.Configuration
                .NORMAL);
        game.printBoard(color);

        Color sideToMove = game.getCurrentTurn();
        while (true) {
            try {
                String move;
                System.out.println(promptMessages.get(sideToMove));
                move = inReaders.get(sideToMove).nextLine();

                if (move.equals("?")) {
                    showHelp();
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

                // After we make a move on the local instance and confirmed that it's valid, send
                // it over the network
                if (sideToMove == color) {
                    remoteOut.println(move);
                }

                game.printBoard(color);
                sideToMove = game.getCurrentTurn();
            } catch (ParseException exception) {
                System.out.println("Invalid move: " + exception.getMessage());
                System.out.println("\t at position " + exception.getErrorOffset());
                System.out.println("Please try again.");
            } catch (NoSuchMoveException | AmbiguousNotationException | KingInCheckException exception) {
                System.out.println(exception.getMessage());
            }
        }
    }

    private void showHelp() {
        System.out.println("\t'q' or 'quit' terminates the program");
        System.out.println("\t'history' displays the move history");
    }
}
