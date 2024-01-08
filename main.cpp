#include <iostream>
#include "game.h"

int main(int argc, char* argv[])
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "Failed to initialize SDL_image for PNG files: " << IMG_GetError << std::endl;
    }
    SDL_Surface* boardSurface = NULL;
    //boardSurface = IMG_Load("./ChessPieces/board.png");

    Game* game = new Game();

    game->init("Mateusz Wieczorek -> Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game->clean();
    return 0;
}

