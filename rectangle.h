#pragma once

#include "SDL.h"

class Rectangle
{
private:
	int boardRow, boardColumn, xPosition, yPosition;

	SDL_Texture* objectTexture;
	SDL_Rect sourceRect, destinationRect;
	SDL_Renderer* renderer;

public:
	Rectangle(const char* filename, SDL_Renderer* ren, int bRow, int bColumn);
	~Rectangle();

	int& getBoardRow() { return boardRow; }
	int& getBoardcolumn() { return boardColumn; }
	void update();
	void render();
	void calculateXY();
};