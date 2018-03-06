package com.keshane.Paw;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.text.ParseException;
import java.util.Scanner;

/**
 * Encapsulates the logic for an instance of Paw initiating a connection
 */
public class Client {

    private static final int SERVER_PORT = 58453;

    private final Socket connectionSocket;

    private static final Color color = Color.WHITE;

    private final String blackName;

    private final String whiteName;

    private final Scanner localIn;

    private final Scanner remoteIn;

    private final PrintWriter remoteOut;

    /**
     * Constructs a remote session and connects to the specified socket
     *
     * @param ipAddressText the IP address of the remote instance of Paw
     */
    Client(String ipAddressText) throws IOException {
        InetSocketAddress remoteSocket = new InetSocketAddress(ipAddressText, SERVER_PORT);
        connectionSocket = new Socket();
        connectionSocket.connect(remoteSocket);

        System.out.println("Connected to " + ipAddressText + ".");

        System.out.println("Enter your name: ");
        localIn = new Scanner(System.in);
        whiteName = localIn.nextLine();
        System.out.println("Waiting on other player to enter name...");

        remoteOut = new PrintWriter(connectionSocket.getOutputStream(), true);
        remoteOut.println(whiteName);

        remoteIn = new Scanner(connectionSocket.getInputStream());
        blackName = remoteIn.nextLine();




        System.out.println("Successful connection!");
        System.out.println("white name: " + whiteName);
        System.out.println("black name: " + blackName);

    }

    /**
     * Run the game
     */
    void startGame() {
        Game game = new Game(whiteName, blackName, Board.Configuration.NORMAL);

        game.printBoard(color);

        Color currentTurn = Color.WHITE;
        while (true) {
            try {
                String move;
                if (currentTurn == color) {
                    System.out.println("Enter move ('q' or 'quit' to exit):");
                    move = localIn.nextLine();
                }
                else {
                    move = remoteIn.nextLine();
                }

                if (move.equalsIgnoreCase("q") || move.equalsIgnoreCase("quit")) {
                    System.out.println("Quitting...");
                    break;
                }
                else if (move.equalsIgnoreCase("history")) {
                    game.printHistory();
                    continue;
                }
                game.makeMove(move);
                if (currentTurn == color) {
                    remoteOut.println(move);
                }
                game.printBoard(color);
                currentTurn = currentTurn.opposite();
            } catch (ParseException exception) {
                System.out.println("Invalid move: " + exception.getMessage());
                System.out.println("\t at position " + exception.getErrorOffset());
                System.out.println("Please try again.");
            } catch (NoSuchMoveException | AmbiguousNotationException | KingInCheckException exception) {
                System.out.println(exception.getMessage());
            }

        }

    }
}
