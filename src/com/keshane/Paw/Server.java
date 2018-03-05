package com.keshane.Paw;

import java.io.*;
import java.net.*;
import java.rmi.Remote;
import java.text.ParseException;
import java.util.*;

/**
 * Manages a game played over a network (using two different instances of Paw)
 */
public class Server {
    /**
     * The address of the opponent
     */
    private InetSocketAddress remoteSocket;

    private InetSocketAddress localSocket;

    private ServerSocket serverSocket;

    private Socket connectionSocket;

    private static final int SERVER_PORT = 58453;

    private String blackName;

    private String whiteName;

    private final Scanner localIn;
    private Scanner remoteIn;

    private PrintWriter remoteOut;

    private static final Color color = Color.BLACK;

    /**
     * Constructs a remote session that other instances of Paw can connect to
     */
    Server() throws IOException {
        // find all the IP addresses available on this machine and give user option to select one
        // to listen on
        Enumeration<NetworkInterface> networkInterfaces = NetworkInterface.getNetworkInterfaces();
        List<InetAddress> ipAddresses = new ArrayList<>();
        for (NetworkInterface networkInterface : Collections.list(networkInterfaces)) {
            ipAddresses.addAll(Collections.list(networkInterface.getInetAddresses()));
        }

        System.out.println("Please select the IP address to listen on.");
        for (int i = 0; i < ipAddresses.size(); i++) {
            System.out.println(i + ": " + ipAddresses.get(i).getHostAddress());
        }


        String selection;
        localIn = new Scanner(System.in);
        selection = localIn.nextLine();

        int selectionIndex = Integer.parseInt(selection);

        localSocket = new InetSocketAddress(ipAddresses.get(selectionIndex), SERVER_PORT);

        serverSocket = new ServerSocket();
        serverSocket.bind(localSocket);

        serve();

    }

    void serve() throws IOException {
        System.out.println("Listening on " + serverSocket.getInetAddress().toString() + ":" +
                SERVER_PORT);
        connectionSocket = serverSocket.accept();

        System.out.println("Enter your name: ");
        blackName = localIn.nextLine();

        remoteOut = new PrintWriter(connectionSocket.getOutputStream(), true);
        remoteOut.println(blackName);

        remoteIn = new Scanner(connectionSocket.getInputStream());
        whiteName = remoteIn.nextLine();

        System.out.println("successful connection!");
        System.out.println("white name: " + whiteName);
        System.out.println("black name: " + blackName);
    }

    /**
     * Run the game
     */
    void startGame() {
        Game game = new Game(whiteName, blackName, Board.Configuration.NORMAL);

        game.printBoard();

        Color currentTurn = Color.WHITE;
        while (true) {
            try {
                System.out.println("Enter move ('q' or 'quit' to exit):");
                String move;
                if (currentTurn == color) {
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
                remoteOut.println(move);
                game.printBoard();
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

    enum Role {
        SERVER,
        CLIENT,
    }
}
