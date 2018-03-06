# Paw
Command-line chess interface in Java

**P**layers  
**a**re  
**w**inners

A program to play chess on the command line locally or over a network.

**Java 8** is required to run this software.

The build is distributed as a `.jar` named `Paw.jar`. Look in releases for the latest build. 

## Local Play
Using a terminal, navigate to the `Paw.jar` file and execute it like so:

    java -jar Paw.jar

The prompts will guide you through the steps to start and play the game.

## Remote Play
Player 1 and Player 2 must be on the same network with the appropriate ports and security 
permissions open.
Player 1 (acting as the server) starts the program with this command:

    java -jar Paw.jar -s
    
Player 1 follows the prompt to establish the listening server. Once Player 1 has completed that
step, Player 2 starts the program with this command:

    java -jar Paw.jar -c <Player 1 IP address>
    
`<Player 1 IP address>` refers to the IP address that Player 1 selected in her prompt.

From there, both players follow the prompts to start and play the game.

 
