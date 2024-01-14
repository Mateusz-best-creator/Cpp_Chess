#pragma once

#include "board.h"

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;

class Game
{
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int choosenRow, choosenColumn;

	// Define flags
	enum class flags { FULLSCREEN = 0 };

	std::unique_ptr<Board> board;
	int playerIndex;

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	bool handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }
};