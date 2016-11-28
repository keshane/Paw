CC = g++
CFLAGS = -std=c++11 -Wall -g3 -pedantic

Paw: chess_gui.o
	$(CC) $^ -o $@

chess_gui.o: chess_gui.cpp chess_gui.h
	$(CC) $(CFLAGS) -c chess_gui.cpp 
