# Tic Tac Toe SDL2 project
#
# Alan Herculano Diniz
#
# Video Reference: https://www.youtube.com/watch?v=gCVMkKgs3uQ&t=827s


# Build variables:

CC = gcc # Compiler used

FLAGS = -Wall `pkg-config --libs SDL2` # Compilation flags

SRC = src # Source code folder

BIN = bin # Binaries folder

EXE = TicTacToe # Name of the program


# Build targets:

all: $(BIN)/$(EXE) # Main build target

# bin/main.o object file target:
$(BIN)/main.o: $(SRC)/main.c
	$(CC) -c $^ -o $@ $(FLAGS)

# Executable program target:
$(BIN)/$(EXE): $(BIN)/main.o
	$(CC) -o $@ $^ $(FLAGS)
