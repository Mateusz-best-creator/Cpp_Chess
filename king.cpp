#include "game.h"
#include "king.h"

King::King(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c)
	: Piece(filename, ren, bRow, bCol, c) 
{
	if (c == WHITE)
	{
		kingRow = 0;
		kingColumn = 4;
	}
	else if (c == BLACK)
	{
		kingRow = 7;
		kingColumn = 4;
	}
}

King::~King() {}

bool King::move(int toRow, int toCol, char blueRectangles[][8])
{
	if (blueRectangles[toRow][toCol] == BLUE_RECTANGLE)
	{
		kingRow = toRow;
		kingColumn = toCol;
		return true;
	}
	return false;
}

void King::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], 
	char blueRectangles[][8], bool forChecks, char whiteColorsSquares[][8], char blackColorsSquares[][8])
{
	if (colors[fromRow][fromCol] == WHITE)
		updateRectangles(BLACK, fromRow, fromCol, board, colors, blueRectangles, forChecks, blackColorsSquares);
	else if (colors[fromRow][fromCol] == BLACK)
		updateRectangles(WHITE, fromRow, fromCol, board, colors, blueRectangles, forChecks, whiteColorsSquares);
}

void King::updateRectangles(char color, int fromRow, int fromCol, int board[][8], char colors[][8], 
	char blueRectangles[][8], bool forChecks, char colorsSquares[][8])
{
	// We start indexing directions from bottom left border
	int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
	for (size_t i = 0; i < 8; i++)
	{
		int dirRow = directions[i][0];
		int dirCol = directions[i][1];

		int toRow = fromRow + dirRow;
		int toCol = fromCol + dirCol;

		if (toRow <= 7 && toRow >= 0 && toCol <= 7 && toCol >= 0)
		{
			if (colors[toRow][toCol] == EMPTY || colors[toRow][toCol] == color || (forChecks && colors[toRow][toCol] != color))
				if (checkIfMoveValid(toRow, toCol, colorsSquares))
					blueRectangles[toRow][toCol] = BLUE_RECTANGLE;
		}
	}
}

bool King::checkIfMoveValid(int toRow, int toColumn, char colorsSquares[][8])
{
	return colorsSquares[toRow][toColumn] == EMPTY;
}