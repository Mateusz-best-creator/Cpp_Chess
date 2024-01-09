#pragma once

#include "SDL.h"
#include "SDL_image.h"

const int PIECE_HEIGHT = 64, PIECE_WIDTH = 64;

class Piece
{
protected:
	int xPosition, yPosition, boardSquare;
	char color;

	SDL_Texture* objectTexture;
	SDL_Rect sourceRect, destinationRect;
	SDL_Renderer* renderer;

public:
	Piece(const char* filename, SDL_Renderer* ren, int x, int y, int bSquare, char c);
	virtual ~Piece() = 0;

	void update();
	void render();

	int getX() { return xPosition; }
	int getY() { return yPosition; }

	virtual void move() = 0;
};
