#include "pawn.h"
#include "textureManager.h"
#include <iostream>

Pawn::Pawn(const char* filename, SDL_Renderer* ren, int bRow, int bColumn, char c)
	: Piece(filename, ren, bRow, bColumn, c)
{}

Pawn::~Pawn() {}

static int previousRow, previousCol;

bool Pawn::move(int toRow, int toCol, char blueRectangles[][8])
{
	return blueRectangles[toRow][toCol] == BLUE_RECTANGLE;
}

void Pawn::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8])
{
	if (colors[fromRow][fromCol] == WHITE)
	{
		if (colors[fromRow + 2][fromCol] == EMPTY && fromRow == 1)
			blueRectangles[fromRow + 2][fromCol] = BLUE_RECTANGLE;
		if (colors[fromRow + 1][fromCol] == EMPTY)
			blueRectangles[fromRow + 1][fromCol] = BLUE_RECTANGLE;
		if (colors[fromRow + 1][fromCol + 1] != EMPTY && colors[fromRow + 1][fromCol + 1] == BLACK)
			blueRectangles[fromRow + 1][fromCol + 1] = BLUE_RECTANGLE;
		if (colors[fromRow + 1][fromCol - 1] != EMPTY && colors[fromRow + 1][fromCol - 1] == BLACK)
			blueRectangles[fromRow + 1][fromCol - 1] = BLUE_RECTANGLE;
	}
	else if (colors[fromRow][fromCol] == BLACK)
	{
		if (colors[fromRow - 2][fromCol] == EMPTY && fromRow == 6)
			blueRectangles[fromRow - 2][fromCol] = BLUE_RECTANGLE;
		if (colors[fromRow - 1][fromCol] == EMPTY)
			blueRectangles[fromRow - 1][fromCol] = BLUE_RECTANGLE;
		if (colors[fromRow - 1][fromCol + 1] != EMPTY && colors[fromRow - 1][fromCol + 1] == WHITE)
			blueRectangles[fromRow - 1][fromCol + 1] = BLUE_RECTANGLE;
		if (colors[fromRow - 1][fromCol - 1] != EMPTY && colors[fromRow - 1][fromCol - 1] == WHITE)
			blueRectangles[fromRow - 1][fromCol - 1] = BLUE_RECTANGLE;
	}
}

