package com.keshane.Paw;

import java.io.*;
import java.net.*;
import java.rmi.Remote;
import java.text.ParseException;
import java.util.*;

/**
 * Manages a game played over a network (using two different instances of Paw)
 */
class Server {

    private Socket connectionSocket;

    private static final int SERVER_PORT = 58453;

    private static final Color color = Color.BLACK;

    private final Session session;

    /**
     * Constructs a remote session that other instances of Paw can connect to
     */
    Server() throws IOException {
        InetAddress ipAddress = promptForIpAddress();

        serve(ipAddress);

        session = new RemoteSession(color, connectionSocket.getInputStream(), connectionSocket
                .getOutputStream());

    }

    private InetAddress promptForIpAddress() throws IOException {
        // find all the IP addresses available on this machine and give user option to select one
        // to listen on
        Enumeration<NetworkInterface> networkInterfaces = NetworkInterface.getNetworkInterfaces();
        List<InetAddress> ipAddresses = new ArrayList<>();
        for (NetworkInterface networkInterface : Collections.list(networkInterfaces)) {
            ipAddresses.addAll(Collections.list(networkInterface.getInetAddresses()));
        }

        System.out.println("Please select the index of the IP address to listen on.");
        for (int i = 0; i < ipAddresses.size(); i++) {
            System.out.println(i + ": " + ipAddresses.get(i).getHostAddress());
        }

        Scanner localIn = new Scanner(System.in);
        String selection = localIn.nextLine();
        int selectionIndex = Integer.parseInt(selection);

        return ipAddresses.get(selectionIndex);

    }

    private void serve(InetAddress ipAddress) throws IOException {
        InetSocketAddress localSocket = new InetSocketAddress(ipAddress, SERVER_PORT);
        ServerSocket serverSocket = new ServerSocket();
        serverSocket.bind(localSocket);

        System.out.println("Listening on " + serverSocket.getInetAddress().toString() + ":" +
                SERVER_PORT);
        connectionSocket = serverSocket.accept();

        System.out.println("Connected to " + ((InetSocketAddress) connectionSocket
                .getRemoteSocketAddress()).getAddress().toString() + ".");
    }

    Session getSession() {
        return session;
    }
}
