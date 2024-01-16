#include "game.h"
#include "queen.h"

Queen::Queen(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c)
	: Piece(filename, ren, bRow, bCol, c), Bishop(filename, ren, bRow, bCol, c), Rook(filename, ren, bRow, bCol, c) {}

Queen::~Queen() {}

bool Queen::move(int toRow, int toCol, char blueRectangles[][8])
{
	return blueRectangles[toRow][toCol] == BLUE_RECTANGLE;
}

void Queen::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8], bool forChecks)
{
	Bishop::displayBlueRectangles(fromRow, fromCol, board, colors, blueRectangles, forChecks);
	Rook::displayBlueRectangles(fromRow, fromCol, board, colors, blueRectangles, forChecks);
}

void Queen::updateRectangles(char color, int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8], bool forChecks)
{
	Bishop::updateRectangles(color, fromRow, fromCol, board, colors, blueRectangles, forChecks);
	Rook::updateRectangles(color, fromRow, fromCol, board, colors, blueRectangles, forChecks);
}