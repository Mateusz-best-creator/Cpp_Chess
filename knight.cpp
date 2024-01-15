#include "knight.h"
#include "game.h"
#include <iostream>

Knight::Knight(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c)
	: Piece(filename, ren, bRow, bCol, c) {}

Knight::~Knight() {}

bool Knight::move(int toRow, int toCol, char blueRectangles[][8])
{
	return true;
	return blueRectangles[toRow][toCol] = BLUE_RECTANGLE;
}

void Knight::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8])
{
	std::cout << static_cast<char>(colors[fromRow][fromCol]) << std::endl;
	if (colors[fromRow][fromCol] == WHITE)
	{
		// top right
		if (fromCol + 1 < 8 && fromRow + 2 < 8 && (colors[fromCol + 1][fromRow + 2] == EMPTY || colors[fromCol + 1][fromRow + 2] == BLACK))
			blueRectangles[fromRow + 2][fromCol + 1] = BLUE_RECTANGLE;
		// top left
		if (fromCol - 1 > 0 && fromRow + 2 < 8 && (colors[fromCol - 1][fromRow + 2] == EMPTY || colors[fromCol - 1][fromRow + 2] == BLACK))
			blueRectangles[fromRow + 2][fromCol - 1] = BLUE_RECTANGLE;
		// bottom right
		if (fromCol + 1 < 8 && fromRow - 2 > 0 && (colors[fromCol + 1][fromRow - 2] == EMPTY || colors[fromCol + 1][fromRow - 2] == BLACK))
			blueRectangles[fromRow - 2][fromCol + 1] = BLUE_RECTANGLE;
		// bottom left
		if (fromCol - 1 > 0 && fromRow - 2 > 0 && (colors[fromCol - 1][fromRow - 2] == EMPTY || colors[fromCol - 1][fromRow - 2] == BLACK))
			blueRectangles[fromRow - 2][fromCol - 1] = BLUE_RECTANGLE;
		// left top
		//if (fromCol)
	}
	if (colors[fromRow][fromCol] == BLACK)
	{

	}
}