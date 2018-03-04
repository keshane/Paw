package com.keshane.Paw;

import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.rmi.Remote;

/**
 * Manages a game played over a network (using two different instances of Paw)
 */
public class RemoteSession {
    /**
     * The address of the opponent
     */
    private InetSocketAddress remoteSocket;

    /**
     * Constructs a remote session and connects to the specified socket
     * @param ipAddressText the IP address of the remote instance of Paw
     * @param portText the port to connect to
     */
    RemoteSession(String ipAddressText, String portText) {
        remoteSocket = new InetSocketAddress(ipAddressText, Integer.parseInt(portText));
    }


    /**
     * Constructs a remote session that other instances of Paw can connect to
     */
    RemoteSession() {
        serve();
    }

    void serve() {

    }

    void connect() {

    }

    enum Role {
        SERVER,
        CLIENT,
    }
}
