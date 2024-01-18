#include "game.h"
#include "king.h"

// We start indexing directions from bottom left border
int directions[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

King::King(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c)
	: Piece(filename, ren, bRow, bCol, c) 
{
	if (c == WHITE)
	{
		kingRow = 0;
		kingColumn = 4;
	}
	else
	{
		kingRow = 7;
		kingColumn = 4;
	}

	kingColor = c;
	check = hasMoved = longCastleRookMoved = shortCastleRookMoved = false;
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
	char opponentColor = (colors[fromRow][fromCol] == WHITE) ? BLACK : WHITE;
	updateRectangles(opponentColor, fromRow, fromCol, board, colors, blueRectangles, forChecks,
		(opponentColor == BLACK) ? blackColorsSquares : whiteColorsSquares);

	for (size_t i = 0; i < 8; i++)
	{
		int toRow, toCol;
		calculateDestination(fromRow, fromCol, directions[i], toRow, toCol);

		if (isValidSquare(toRow, toCol))
		{
			char(*targetColorsSquares)[8] = (colors[fromRow][fromCol] == WHITE) ? whiteColorsSquares : blackColorsSquares;
			targetColorsSquares[toRow][toCol] = BLUE_RECTANGLE;
		}
	}
	
	// Only if king didnt move we can make a castle
	if (!hasMoved)
	{
		// Short castle
		if (!shortCastleRookMoved)
		{
			if (colors[fromRow][fromCol] == WHITE)
			{
				if (blackColorsSquares[0][5] == EMPTY && blackColorsSquares[0][6] == EMPTY &&
					colors[0][5] == EMPTY && colors[0][6] == EMPTY)
				{
					blueRectangles[0][6] = BLUE_RECTANGLE;
				}

			}
			else if (colors[fromRow][fromCol] == BLACK)
			{
				if (whiteColorsSquares[7][5] == EMPTY && whiteColorsSquares[7][6] == EMPTY &&
					colors[7][5] == EMPTY && colors[7][6] == EMPTY)
				{
					blueRectangles[7][6] = BLUE_RECTANGLE;
				}
			}
		}
		// Long castle
		if (!longCastleRookMoved)
		{
			if (colors[fromRow][fromCol] == WHITE)
			{
				if (blackColorsSquares[0][1] == EMPTY && blackColorsSquares[0][2] == EMPTY && blackColorsSquares[0][3] == EMPTY 
					&& colors[0][1] == EMPTY && colors[0][2] == EMPTY && colors[0][3] == EMPTY)
				{
					blueRectangles[0][2] = BLUE_RECTANGLE;
				}
			}
			else if (colors[fromRow][fromCol] == BLACK)
			{
				if (whiteColorsSquares[7][1] == EMPTY && whiteColorsSquares[7][2] == EMPTY && whiteColorsSquares[7][3] == EMPTY
					&& colors[7][1] == EMPTY && colors[7][2] == EMPTY && colors[7][3] == EMPTY)
				{
					blueRectangles[7][2] = BLUE_RECTANGLE;
				}
			}
		}
	}
}

void King::updateRectangles(char color, int fromRow, int fromCol, int board[][8], char colors[][8],
	char blueRectangles[][8], bool forChecks, char colorsSquares[][8])
{
	for (size_t i = 0; i < 8; i++)
	{
		int toRow, toCol;
		calculateDestination(fromRow, fromCol, directions[i], toRow, toCol);

		if (isValidSquare(toRow, toCol))
		{
			if (isValidMove(color, toRow, toCol, colors, forChecks, colorsSquares))
				blueRectangles[toRow][toCol] = BLUE_RECTANGLE;
		}
	}
}

void King::calculateDestination(int fromRow, int fromCol, int direction[], int& toRow, int& toCol)
{
	int dirRow = direction[0];
	int dirCol = direction[1];
	toRow = fromRow + dirRow;
	toCol = fromCol + dirCol;
}

bool King::isValidSquare(int row, int col)
{
	return (row >= 0 && row <= 7 && col >= 0 && col <= 7);
}

bool King::isValidMove(char color, int toRow, int toCol, char colors[][8], bool forChecks, char colorsSquares[][8])
{
	return (colors[toRow][toCol] == EMPTY || colors[toRow][toCol] == color || (forChecks && colors[toRow][toCol] != color))
		&& checkIfMoveValid(toRow, toCol, colorsSquares);
}


bool King::checkIfMoveValid(int toRow, int toColumn, char colorsSquares[][8])
{
	return colorsSquares[toRow][toColumn] == EMPTY;
}

bool King::checkIfCheck(char boardToCheck[][8])
{
	check =  boardToCheck[kingRow][kingColumn] != EMPTY;
	return check;
}

bool King::checkIfCheckmate(int board[][8], char colors[][8], char colorsSquares[][8])
{
	if (check)
	{
		// Check if there are some blue rectangles for king available
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (colorsSquares[i][j] != EMPTY)
					return false;
			}
		}
		return true;
	}
	return false;
}