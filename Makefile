CC = g++
CFLAGS = -std=c++11 -Wall -g3 -pedantic

Paw: chess_gui.o Board.o Game.o Player.o Parser.o utility.o entities.o
	$(CC) $(CFLAGS) $^ -o $@

testparser: tests/test_parser.cpp Parser.cpp utility.cpp entities.cpp
	$(CC) $(CFLAGS) $^ -o $@

utility.o: utility.cpp
	$(CC) $(CFLAGS) -c $^ 

entities.o: entities.cpp
	$(CC) $(CFLAGS) -c $^ 

Parser.o: Parser.cpp
	$(CC) $(CFLAGS) -c $^ 

Player.o: Player.cpp
	$(CC) $(CFLAGS) -c $^ 

Board.o: Board.cpp
	$(CC) $(CFLAGS) -c $^ 

Game.o: Game.cpp
	$(CC) $(CFLAGS) -c $^ 

chess_gui.o: chess_gui.cpp
	$(CC) $(CFLAGS) -c $^ 