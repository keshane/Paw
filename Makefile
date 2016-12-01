CC = g++
CFLAGS = -std=c++11 -Wall -g3 -pedantic

Paw: chess_gui.o Board.o
	$(CC) $^ -o $@

Board.o: Board.cpp chess_gui.h
	$(CC) $(CFLAGS) -c Board.cpp 

chess_gui.o: chess_gui.cpp
	$(CC) $(CFLAGS) -c chess_gui.cpp 
