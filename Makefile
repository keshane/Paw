CC = g++
CFLAGS = -std=c++11 -Wall -g3 -pedantic

Paw: chess_gui.o Board.o Game.o Player.o Parser.o
	$(CC) $^ -o $@

chess_gui.o: chess_gui.cpp
	$(CC) $(CFLAGS) -c chess_gui.cpp 

Board.o: Board.cpp
	$(CC) $(CFLAGS) -c Board.cpp 

Game.o: Game.cpp
	$(CC) $(CFLAGS) -c Game.cpp 

Player.o: Player.cpp
	$(CC) $(CFLAGS) -c Player.cpp 

Parser.o: Parser.cpp
	$(CC) $(CFLAGS) -c Parser.cpp 
