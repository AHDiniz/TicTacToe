#include "../include/game.h"
#include <math.h>

const SDL_Color xColor = {.r = 255, .g = 50, .b = 50};
const SDL_Color oColor = {.r = 50, .g = 100, .b = 255};
const SDL_Color tieColor = {.r = 100, .g = 100, .b = 100};
const SDL_Color gridColor = {.r = 255, .g = 255, .b = 255};

static void RenderGrid(SDL_Renderer *renderer, const SDL_Color *color)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);

    for (int i = 1; i < N; i++)
    {
        SDL_RenderDrawLine(renderer, i * CELL_WIDTH, 0, i * CELL_WIDTH, SCREEN_HEIGHT);
        SDL_RenderDrawLine(renderer, 0, i * CELL_HEIGHT, SCREEN_WIDTH, i * CELL_HEIGHT);
    }
}

static void RenderX(SDL_Renderer *renderer, int row, int col, const SDL_Color *color)
{
    const float halfBoxSize = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
    const float centerX = CELL_WIDTH * 0.5 + col * CELL_WIDTH;
    const float centerY = CELL_HEIGHT * 0.5 = row * CELL_HEIGHT;

    
}

static void RenderO(SDL_Renderer *renderer, int row, int col, const SDL_Color *color)
{

}

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

static void RunningRender(SDL_Renderer *renderer, const Game *game)
{
    RenderGrid(renderer, &gridColor);
    RenderBoard(renderer, game->board, &xColor, &oColor);
}

static void GameOverRender(SDL_Renderer *renderer, const Game *game, const SDL_Color *color)
{
    RenderGrid(renderer, color);
    RenderBoard(renderer, game->board, color, color);
}

void Game_Render(SDL_Renderer *renderer, const Game *game)
{
    switch (game->currentState)
    {
        case Running:
            RunningRender(renderer, game);
            break;
        case XWin:
            GameOverRender(renderer, game, &xColor);
            break;
        case OWin:
            GameOverRender(renderer, game, &oColor);
            break;
        case Tie:
            GameOverRender(renderer, game, &tieColor);
            break;
        default:
            break;
    }
}

void Game_ClickOnCell(Game *game, int row, int col)
{
}
