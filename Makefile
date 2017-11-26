CC = g++
CFLAGS = -std=c++11 -Wall -g3 -pedantic

Paw: chess_gui.cpp Board.cpp Game.cpp Player.cpp Parser.cpp utility.cpp entities.cpp
	$(CC) $(CFLAGS) $^ -o $@

testparser: tests/test_parser.cpp Parser.cpp utility.cpp entities.cpp
	$(CC) $(CFLAGS) $^ -o $@