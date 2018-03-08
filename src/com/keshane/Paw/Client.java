package com.keshane.Paw;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;

/**
 * Encapsulates the logic for an instance of Paw initiating a connection
 */
class Client {

    private static final int SERVER_PORT = 58453;

    private final Socket connectionSocket;

    private static final Color color = Color.WHITE;

    private final Session session;

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

        session = new RemoteSession(color, connectionSocket.getInputStream(), connectionSocket
                .getOutputStream());

    }

    Session getSession() {
        return session;
    }


}
