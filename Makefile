# Tic Tac Toe SDL2 project
#
# Alan Herculano Diniz
#
# Video Reference: https://www.youtube.com/watch?v=gCVMkKgs3uQ&t=827s
#
# Build file


# Build variables:

CC = gcc # Compiler used

FLAGS = -Wall -lSDL2main -lSDL2 -lm `pkg-config --libs SDL2` # Compilation flags

LIB = lib # Folder with the libraries used

# Name of the program according to the operetional system:
ifeq ($(OS), Windows_NT)
	EXE = TicTacToe.exe
else
	EXE = TicTacToe.out
endif


# Build targets:

all: bin/$(EXE) # Main build target

# Executable program target:
bin/$(EXE): $(wildcard src/*.c)
	$(CC) -o $@ $^ $(FLAGS)
