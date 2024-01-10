#pragma once

#include "SDL.h"
#include "SDL_image.h"

const int PIECE_HEIGHT = 64, PIECE_WIDTH = 64;

class Piece
{
protected:
	int xPosition, yPosition, boardRow, boardColumn;
	char color;

	SDL_Texture* objectTexture;
	SDL_Rect sourceRect, destinationRect;
	SDL_Renderer* renderer;

public:
	Piece(const char* filename, SDL_Renderer* ren, int bRow, int bColumn, char c);
	virtual ~Piece() = 0;
	
	void calculateXY();
	void update();
	void render();

	int getX() { return xPosition; }
	int getY() { return yPosition; }

	virtual void move() = 0;
};
