#pragma once

#include "SDL.h"
#include "SDL_image.h"

const int PIECE_HEIGHT = 64, PIECE_WIDTH = 64;

class Piece
{
private:
	SDL_Texture* objectTexture;
	SDL_Rect sourceRect, destinationRect;
	SDL_Renderer* renderer;

protected:
	int xPosition, yPosition, boardRow, boardColumn;
	char color;

public:
	Piece(const char* filename, SDL_Renderer* ren, int bRow, int bColumn, char c);
	virtual ~Piece() = 0;
	
	virtual void calculateXY();
	void update();
	void render();
	int absoluteValue(int a, int b);

	virtual bool move(int toRow, int toCol, char blueRectangles[][8]) = 0;
	virtual void displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8], bool forChecks) = 0;
};