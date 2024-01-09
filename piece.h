#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

const int PIECE_HEIGHT = 64, PIECE_WIDTH = 64;

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

	void p_pos() { std::cout << xPosition << " " << yPosition << std::endl; }

};