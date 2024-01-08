#pragma once

#include "board.h"
#include <iostream>

class Game
{
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;

	// Define flags
	enum class flags { FULLSCREEN = 0 };

	Board* board;

public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }
};