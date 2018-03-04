package com.keshane.Paw;

import java.io.*;
import java.net.*;
import java.rmi.Remote;
import java.util.*;

/**
 * Manages a game played over a network (using two different instances of Paw)
 */
public class RemoteSession {
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

    /**
     * Constructs a remote session and connects to the specified socket
     *
     * @param ipAddressText the IP address of the remote instance of Paw
     * @param portText      the port to connect to
     */
    RemoteSession(String ipAddressText, String portText) throws IOException {
        remoteSocket = new InetSocketAddress(ipAddressText, Integer.parseInt(portText));
        connectionSocket = new Socket();
        connectionSocket.connect(remoteSocket);

        Scanner in = new Scanner(connectionSocket.getInputStream());
        blackName = in.nextLine();

        System.out.println("Enter your name: ");
        Scanner inLocal = new Scanner(System.in);
        whiteName = inLocal.nextLine();

        PrintWriter out = new PrintWriter(connectionSocket.getOutputStream(), true);
        out.println(whiteName);

        System.out.println("String successful connection!");
        System.out.println("white name: " + whiteName);
        System.out.println("black name: " + blackName);

    }


    /**
     * Constructs a remote session that other instances of Paw can connect to
     */
    RemoteSession() throws IOException {
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
        Scanner in = new Scanner(System.in);
        selection = in.nextLine();

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
        Scanner in = new Scanner(System.in);
        String blackName = in.nextLine();

        PrintWriter out = new PrintWriter(connectionSocket.getOutputStream(), true);
        out.println(blackName);

        Scanner inRemote = new Scanner(connectionSocket.getInputStream());
        whiteName = inRemote.nextLine();

        System.out.println("successful connection!");
        System.out.println("white name: " + whiteName);
        System.out.println("black name: " + blackName);
    }

    InputStream getInputStream() throws IOException {
        return connectionSocket.getInputStream();
    }

    OutputStream getOutputStream() throws IOException {
        return connectionSocket.getOutputStream();
    }


    enum Role {
        SERVER,
        CLIENT,
    }
}
