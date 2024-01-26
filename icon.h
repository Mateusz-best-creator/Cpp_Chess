#pragma once

#include "SDL.h"

const int ICON_WIDTH = 100, ICON_HEIGHT = 100;

class Icon
{
private:
	SDL_Texture* objectTexture;
	SDL_Rect sourceRect, destinationRect;
	SDL_Renderer* renderer;

	int destinationX, destinationY;

public:
	Icon(const char* filename, SDL_Renderer* ren);
	~Icon();

	void update();
	void render();
};