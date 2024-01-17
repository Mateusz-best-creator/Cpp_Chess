#include "game.h"

Game::Game()
{
	choosenRow = choosenColumn = 0;
	isRunning = false;
	window = nullptr;
	renderer = nullptr;
	playerIndex = 1; // white pieces starts
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
}

bool Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		return true;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			isRunning = false;
		}
		return true;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT) 
		{
			int xValue = event.button.x;
			int yValue = event.button.y;
			if (xValue < X_OFFSET || xValue > SCREEN_WIDTH - X_OFFSET || yValue < Y_OFFSET || yValue > SCREEN_HEIGHT - Y_OFFSET)
				return false;
			
			int boardColumn = (xValue - X_OFFSET) / PIECES_X_DISTANCE + 1;
			int boardRow = (yValue - Y_OFFSET) / PIECES_Y_DISTANCE + 1;

			boardRow = 9 - boardRow;
			boardRow = (boardRow < 1) ? 8 : boardRow;
			choosenRow = boardRow;
			choosenColumn = boardColumn;

			try
			{
				board->movingPiece(choosenRow, choosenColumn, playerIndex);
			}
			catch (InvalidIndexException& e)
			{
				std::cout << e.what();
				e.message();
			}
		}
		return true;
	default:
		return false;
	}
	return false;
}

void Game::update()
{
	if (!board->update())
		isRunning = false;
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