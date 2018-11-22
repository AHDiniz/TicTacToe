/**
 * Tic Tac Toe SDL2 project
 * 
 * Alan Herculano Diniz
 * 
 * Video Reference: https://www.youtube.com/watch?v=gCVMkKgs3uQ&t=827s
 * 
 * main.c: program's entry point
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/game.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING); // Initializing the SDL modules

    // Creating the game window:
    SDL_Window *window = SDL_CreateWindow("Tic Tac Toe", 100, 100, SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_SHOWN);
    // Checking for window creation errors:
    if (window == NULL)
    {
        printf("ERROR! The SDL Window could not be created. SDL Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Creating the window's renderer:
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // Checking for renderer creation errors:
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        printf("ERROR! The SDL Renderer could not be created. SDL Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Creating a new game:
    Game game = {
        .board = {
            Empty, Empty, Empty,
            Empty, Empty, Empty,
            Empty, Empty, Empty
        },
        .currentPlayer = PlayerX,
        .currentState = Running
    };

    // Making the game loop:
    SDL_Event e; // This will be used to get the player input:
    while (game.currentState != Quit)
    {
        while (SDL_PollEvent(&e)) // Analysing the event
        {
            switch (e.type) // Checking the event type
            {
                case SDL_QUIT: // If the window's close button is pressed...
                    game.currentState = Quit; // The game state will change to Quit, so the program can close
                    break;
                default:
                    break;
            }

            // Cleaning the screen:
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }

    // Destroying the SDL structures:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit(); // Closing the SDL modules

    return EXIT_SUCCESS;
}
