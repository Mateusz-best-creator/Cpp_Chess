#include "knight.h"
#include "game.h"

Knight::Knight(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c)
	: Piece(filename, ren, bRow, bCol, c) {}

Knight::~Knight() {}

bool Knight::move(int toRow, int toCol, char blueRectangles[][8])
{
	return blueRectangles[toRow][toCol] = BLUE_RECTANGLE;
}

void Knight::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8])
{

}