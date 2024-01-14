#include "pawn.h"
#include "textureManager.h"
#include <iostream>
Pawn::Pawn(const char* filename, SDL_Renderer* ren, int bRow, int bColumn, char c)
	: Piece(filename, ren, bRow, bColumn, c)
{}

Pawn::~Pawn() {}

static int previousRow, previousCol;

bool Pawn::move(int fromRow, int fromCol, int toRow, int toCol, int board[][WIDTH], char colors[][WIDTH], char blueRectangles[][8])
{
	std::cout << "Blue rectangles: " << static_cast<char>(blueRectangles[toRow][toCol]) << std::endl;
	if (colors[fromRow][fromCol] == WHITE)
	{
		// We cant move backward
		if (toRow <= fromRow)
			return false;
		if (absoluteValue(fromCol, toCol) > 1)
			return false;
		if ((fromRow != 1 && absoluteValue(toRow, fromRow) >= 2) || absoluteValue(toRow, fromRow) > 2)
			return false;
		if (fromCol - toCol == 1 && board[fromRow + 1][fromCol - 1] == NONE)
			return false;
		if (toCol - fromCol == 1 && board[fromRow + 1][fromCol + 1] == NONE)
			return false;
	}
	else if (colors[fromRow][fromCol] == BLACK)
	{
		// We cant move backward
		if (toRow >= fromRow)
			return false;
		if (absoluteValue(fromCol, toCol) > 1)
			return false;
		if ((fromRow != 6 && absoluteValue(toRow, fromRow) >= 2) || absoluteValue(toRow, fromRow) > 2)
			return false;
		if (fromCol - toCol == 1 && board[fromRow - 1][fromCol - 1] == NONE)
			return false;
		if (toCol - fromCol == 1 && board[fromRow - 1][fromCol + 1] == NONE)
			return false;
	}
	return true;
}

void Pawn::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8])
{
	if (colors[fromRow][fromCol] == WHITE)
	{
		if (board[fromRow + 2][fromCol] == NONE && fromRow == 1)
			blueRectangles[fromRow + 2][fromCol] = BLUE_RECTANGLE;
		if (board[fromRow + 1][fromCol] == NONE)
			blueRectangles[fromRow + 1][fromCol] = BLUE_RECTANGLE;
		if (board[fromRow + 1][fromCol + 1] != NONE && colors[fromRow + 1][fromCol + 1] == BLACK)
			blueRectangles[fromRow + 1][fromCol + 1] = BLUE_RECTANGLE;
		if (board[fromRow + 1][fromCol - 1] != NONE && colors[fromRow + 1][fromCol - 1] == BLACK)
			blueRectangles[fromRow + 1][fromCol - 1] = BLUE_RECTANGLE;
	}
	else if (colors[fromRow][fromCol] == BLACK)
	{
		if (board[fromRow - 2][fromCol] == NONE && fromRow == 6)
			blueRectangles[fromRow - 2][fromCol] = BLUE_RECTANGLE;
		if (board[fromRow - 1][fromCol] == BLUE_RECTANGLE)
			blueRectangles[fromRow - 1][fromCol] = BLUE_RECTANGLE;
		if (board[fromRow - 1][fromCol + 1] != NONE && colors[fromRow - 1][fromCol + 1] == WHITE)
			blueRectangles[fromRow - 1][fromCol + 1] = BLUE_RECTANGLE;
		if (board[fromRow - 1][fromCol - 1] != NONE && colors[fromRow - 1][fromCol - 1] == WHITE)
			blueRectangles[fromRow - 1][fromCol - 1] = BLUE_RECTANGLE;
	}
}