# Tic Tac Toe SDL2 project
#
# Alan Herculano Diniz
#
# Video Reference: https://www.youtube.com/watch?v=gCVMkKgs3uQ&t=827s
#
# Build file


# Build variables:

CC = gcc # Compiler used

FLAGS = -Wall -lSDL2main -lSDL2 `pkg-config --libs SDL2` # Compilation flags

LIB = lib # Folder with the libraries used

# Name of the program according to the operetional system:
ifeq ($(OS), Windows_NT)
	EXE = TicTacToe.exe
else
	EXE = TicTacToe.out
endif


# Build targets:

all: bin/$(EXE) # Main build target

# bin/main.o object file target:
bin/main.o: src/main.c
	$(CC) -c $^ -o $@ $(FLAGS)

# bin/game.o object file target:
bin/game.o: src/game.c
	$(CC) -c $^ -o $@ $(FLAGS)

# Executable program target:
bin/$(EXE): bin/main.o bin/game.o
	$(CC) -o $@ $^ $(FLAGS)
