#include "game.h"
#include "king.h"

King::King(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c)
	: Piece(filename, ren, bRow, bCol, c) {}

King::~King() {}

bool King::move(int toRow, int toCol, char blueRectangles[][8])
{
	return blueRectangles[toRow][toCol] == BLUE_RECTANGLE;
}

void King::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8])
{

}

void King::updateRectangles(char color, int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8])
{

}