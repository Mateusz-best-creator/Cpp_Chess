#include "pawn.h"
#include "textureManager.h"
#include <iostream>
Pawn::Pawn(const char* filename, SDL_Renderer* ren, int bRow, int bColumn, char c)
	: Piece(filename, ren, bRow, bColumn, c)
{}

Pawn::~Pawn() {}

static int previousRow, previousCol;

bool Pawn::move(int fromRow, int fromCol, int toRow, int toCol, int board[][WIDTH], char colors[][WIDTH])
{
	std::cout << fromRow << " " << fromCol << " " << toRow << " " << toCol << std::endl;
	if (colors[fromRow][fromCol] == 'w')
	{
		// We cant move backward
		if (toRow <= fromRow)
			return false;
		if (absoluteValue(fromCol, toCol) > 1)
			return false;
		if ((fromRow != 1 && absoluteValue(toRow, fromRow) >= 2) || absoluteValue(toRow, fromRow) > 2)
			return false;
		if (fromCol - toCol == 1 && board[fromRow + 1][fromCol - 1] == 0)
			return false;
		if (toCol - fromCol == 1 && board[fromRow + 1][fromCol + 1] == 0)
			return false;
	}
	else if (colors[fromRow][fromCol] == 'b')
	{
		// We cant move backward
		if (toRow >= fromRow)
			return false;
		if (absoluteValue(fromCol, toCol) > 1)
			return false;
		if ((fromRow != 6 && absoluteValue(toRow, fromRow) >= 2) || absoluteValue(toRow, fromRow) > 2)
			return false;
		if (fromCol - toCol == 1 && board[fromRow - 1][fromCol - 1] == 0)
			return false;
		if (toCol - fromCol == 1 && board[fromRow - 1][fromCol + 1] == 0)
			return false;
	}
	return true;
}

void Pawn::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8])
{
	if (colors[fromRow][fromCol] == 'w')
	{
		if (board[fromRow + 2][fromCol] == 0 && fromRow == 1)
			blueRectangles[fromRow + 2][fromCol] = 'b';
		if (board[fromRow + 1][fromCol] == 0)
			blueRectangles[fromRow + 1][fromCol] = 'b';
		if (board[fromRow + 1][fromCol + 1] == 6 && colors[fromRow + 1][fromCol + 1] == 'b')
			blueRectangles[fromRow + 1][fromCol + 1] = 'b';
		if (board[fromRow + 1][fromCol - 1] == 6 && colors[fromRow + 1][fromCol - 1] == 'b')
			blueRectangles[fromRow + 1][fromCol - 1] = 'b';
	}
	else if (colors[fromRow][fromCol] == 'b')
	{
		if (board[fromRow - 2][fromCol] == 0 && fromRow == 6)
			blueRectangles[fromRow - 2][fromCol] = 'w';
		if (board[fromRow - 1][fromCol] == 0)
			blueRectangles[fromRow - 1][fromCol] = 'w';
		if (board[fromRow - 1][fromCol + 1] == 6 && colors[fromRow - 1][fromCol + 1] == 'w')
			blueRectangles[fromRow - 1][fromCol + 1] = 'w';
		if (board[fromRow - 1][fromCol - 1] == 6 && colors[fromRow - 1][fromCol - 1] == 'w')
			blueRectangles[fromRow - 1][fromCol - 1] = 'w';
	}
}