#include "game.h"

Game::Game()
{
}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			std::cout << "Window properly initialized..." << std::endl;


		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer properly created..." << std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	board = std::make_unique<Board>("ChessPieces/board.png", renderer);
	interface = std::make_unique<Interface>();
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			isRunning = false;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) 
		{
			std::cout << event.button.x << " " << event.button.y << std::endl;
			int board_row = (event.button.x - X_OFFSET) / PIECES_X_DISTANCE + 1;
			int board_column = (event.button.y - Y_OFFSET) / PIECES_Y_DISTANCE + 1;
			board_column = 9 - board_column;
			board_column = (board_column < 1) ? 8 : board_column;

			std::cout << board_row << " " << board_column << std::endl;
		}
		break;
	default:
		break;
	}
}

void Game::update()
{
	board->update();
	interface->printInterface();
}

/*
	This is where we add all out textures to be rendered
*/
void Game::render()
{
	SDL_RenderClear(renderer);
	board->render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}