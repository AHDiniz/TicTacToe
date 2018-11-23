/**
 * Tic Tac Toe SDL2 project
 * 
 * Alan Herculano Diniz
 * 
 * Video Reference: https://www.youtube.com/watch?v=gCVMkKgs3uQ&t=827s
 * 
 * game.h: game definition file
 */

#ifndef GAME_H_

#define GAME_H_

#define N 3 // Dimensions of the game board

#define SCREEN_WIDTH  640 // The width of the screen
#define SCREEN_HEIGHT 420 // The height of the screen

#define CELL_WIDTH  (SCREEN_WIDTH / N)
#define CELL_HEIGHT (SCREEN_HEIGHT / N)

#include <SDL2/SDL.h>

// Defining the player data type:
typedef enum
{
    Empty = 0, PlayerX = 1, PlayerO = 2
} Player;

// Defining the game state data type:
typedef enum
{
    Running = 0, XWin = 1, OWin = 2, Tie = 3, Quit = 4
} GameState;

// Defining the game data type:
typedef struct game
{
    Player board[N * N]; // The game board
    Player currentPlayer; // This will hold current turn's player
    GameState currentState; // The game's current state
} Game;

// Defining the function that draws the game in the screen:
void Game_Render(SDL_Renderer *renderer, const Game *game);

// Defining the function that checks for a ouse button click in the screen:
void Game_ClickOnCell(Game *game, int row, int col);

#endif // GAME_H_