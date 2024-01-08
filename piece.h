#pragma once

#include "SDL.h"
#include "SDL_image.h"

class Piece
{
private:
	int xPosition, yPosition;

	SDL_Texture* objectTexture;
	SDL_Rect sourceRect, destinationRect;
	SDL_Renderer* renderer;

public:
	Piece(const char* filename, SDL_Renderer* ren, int x, int y);
	~Piece();

	void update();
	void render();

};