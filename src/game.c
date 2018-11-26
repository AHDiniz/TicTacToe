#include "../include/game.h"
#include "../include/SDL2_gfxPrimitives.h"
#include <math.h>

// Cross color (red)
const SDL_Color xColor = {.r = 255, .g = 50, .b = 50};
// Circle color (blue)
const SDL_Color oColor = {.r = 50, .g = 100, .b = 255};
// Tie color (grey)
const SDL_Color tieColor = {.r = 100, .g = 100, .b = 100};
// Grid color (white)
const SDL_Color gridColor = {.r = 255, .g = 255, .b = 255};

// Function that draws the grid in the screen:
static void RenderGrid(SDL_Renderer *renderer, const SDL_Color *color)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255); // Setting the color to the one given

    // Drawing the grid:
    for (int i = 1; i < N; i++)
    {
        SDL_RenderDrawLine(renderer, i * CELL_WIDTH, 0, i * CELL_WIDTH, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, i * CELL_HEIGHT, SCREEN_WIDTH, i * CELL_HEIGHT);
    }
}

// Function that draws a cross in the screen given it's position and it's color:
static void RenderX(SDL_Renderer *renderer, int row, int col, const SDL_Color *color)
{
    const float halfBoxSize = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25; // Defining the size of the box
    // Defining the center coordinates:
    const float centerX = CELL_WIDTH * 0.5 + col * CELL_WIDTH;
    const float centerY = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    // Drawing the cross:
    thickLineRGBA(renderer, centerX - halfBoxSize, centerY - halfBoxSize, centerX + halfBoxSize, centerY + halfBoxSize, 10, color->r, color->g, color->b, 255);
    thickLineRGBA(renderer, centerX + halfBoxSize, centerY - halfBoxSize, centerX - halfBoxSize, centerY + halfBoxSize, 10, color->r, color->g, color->b, 255);
}

// Function that draws a circle in the screen given it's position and it's color:
static void RenderO(SDL_Renderer *renderer, int row, int col, const SDL_Color *color)
{
    const float halfBoxSize = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25; // Defining the size of the box
    // Defining the center coordinates:
    const float centerX = CELL_WIDTH * 0.5 + col * CELL_WIDTH;
    const float centerY = CELL_HEIGHT * 0.5 + row * CELL_HEIGHT;

    // Drawing the circle:
    filledCircleRGBA(renderer, centerX, centerY, halfBoxSize, color->r, color->g, color->b, 255);
    filledCircleRGBA(renderer, centerX, centerY, halfBoxSize - 5, 0, 0, 0, 255);
}

// Function that draws the board in the screen:
static void RenderBoard(SDL_Renderer *renderer, const Player *board, const SDL_Color *x, const SDL_Color *o)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            switch (board[i * N + j])
            {
                case PlayerX:
                    RenderX(renderer, i, j, x);
                    break;
                case PlayerO:
                    RenderO(renderer, i, j, o);
                    break;
                default:
                    break;
            }
        }
    }
}

// Function that draws the game in the running state:
static void RunningRender(SDL_Renderer *renderer, const Game *game)
{
    RenderGrid(renderer, &gridColor);
    RenderBoard(renderer, game->board, &xColor, &oColor);
}

// Function that draws the game in the game over states:
static void GameOverRender(SDL_Renderer *renderer, const Game *game, const SDL_Color *color)
{
    RenderGrid(renderer, color);
    RenderBoard(renderer, game->board, color, color);
}

// Function that renders the game:
void Game_Render(SDL_Renderer *renderer, const Game *game)
{
    switch (game->currentState) // Checking the current state
    {
        case Running: // Running state
            RunningRender(renderer, game);
            break;
        case XWin: // Game over with a cross win
            GameOverRender(renderer, game, &xColor);
            break;
        case OWin: // Game over with a circle win
            GameOverRender(renderer, game, &oColor);
            break;
        case Tie: // Game over with a tie
            GameOverRender(renderer, game, &tieColor);
            break;
        default:
            break;
    }
}

// Function that switches the players
static void SwitchPlayer(Game *game)
{
    if (game->currentPlayer == PlayerX) game->currentPlayer = PlayerO;
    else if (game->currentPlayer == PlayerO) game->currentPlayer = PlayerX;
}

// Function that checks if a given player won
static int PlayerWinCheck(Game *game, Player player)
{
    int rows = 0;
    int cols = 0;
    int d1Count = 0;
    int d2Count = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (game->board[i * N + j] == player) rows++;
            if (game->board[j * N + i] == player) cols++;
        }

        if (rows >= N || cols >= N) return 1;

        rows = cols = 0;

        if (game->board[i * N + i] == player) d1Count++;
        if (game->board[i * N + N - i - 1] == player) d2Count++;
    }

    return d1Count >= N || d2Count >= N;
}

static int CellCount(Game *game, Player cell)
{
    int count = 0;

    for (int i = 0; i < N * N; i++)
        if (game->board[i] == cell) count++;

    return count;
}

static void GameOverCheck(Game *game)
{
    if (PlayerWinCheck(game, PlayerX))
    {
        game->currentState = XWin;
    }
    else if (PlayerWinCheck(game, PlayerO))
    {
        game->currentState = OWin;
    }
    else if (CellCount(game, Empty) == 0)
    {
        game->currentState = Tie;
    } 
}

static void PlayerTurn(Game *game, int row, int col)
{
    if (game->board[row * N + col] == Empty)
    {
        game->board[row * N + col] = game->currentPlayer;
        SwitchPlayer(game);
        GameOverCheck(game);
    }
}

static void ResetGame(Game *game)
{
    game->currentPlayer = PlayerX;
    game->currentState = Running;
    for (int i = 0; i < N * N; i++) game->board[i] = Empty;
}

void Game_ClickOnCell(Game *game, int row, int col)
{
    if (game->currentState == Running)
    {
        PlayerTurn(game, row, col);
    }
    else
    {
        ResetGame(game);
    }
}
