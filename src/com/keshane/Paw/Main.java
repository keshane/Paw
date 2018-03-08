package com.keshane.Paw;

import java.io.IOException;
import java.text.ParseException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws IOException {
        Session session;
        // client
        if (args.length == 2 && args[0].equalsIgnoreCase("-c")) {
            Client pawClient = new Client(args[1]);
            session = pawClient.getSession();
        }
        // server
        else if (args.length == 1 && args[0].equalsIgnoreCase("-s")) {
            Server pawServer = new Server();
            session = pawServer.getSession();
        }
        else if (args.length == 1 && args[0].equalsIgnoreCase("test")) {
            session = new LocalSession(Board.Configuration.TEST);
        }
        else {
            session = new LocalSession(Board.Configuration.NORMAL);
        }

        session.runGame();
    }
}
