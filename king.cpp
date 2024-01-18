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
		int castleIndex = colors[fromRow][fromCol] == WHITE ? 0 : 7;
		// Short castle
		if (!shortCastleRookMoved)
		{
			if ((blackColorsSquares[castleIndex][5] == EMPTY && blackColorsSquares[castleIndex][6] == EMPTY &&
				colors[castleIndex][5] == EMPTY && colors[castleIndex][6] == EMPTY) ||
				(whiteColorsSquares[castleIndex][5] == EMPTY && whiteColorsSquares[castleIndex][6] == EMPTY &&
					colors[castleIndex][5] == EMPTY && colors[castleIndex][6] == EMPTY))
			{
				blueRectangles[castleIndex][6] = BLUE_RECTANGLE;
			}
		}
		// Long castle
		if (!longCastleRookMoved)
		{
			if ((blackColorsSquares[castleIndex][1] == EMPTY && blackColorsSquares[castleIndex][2] == EMPTY && blackColorsSquares[castleIndex][3] == EMPTY &&
				colors[castleIndex][1] == EMPTY && colors[castleIndex][2] == EMPTY && colors[castleIndex][3] == EMPTY) ||
				(whiteColorsSquares[castleIndex][1] == EMPTY && whiteColorsSquares[castleIndex][2] == EMPTY && whiteColorsSquares[castleIndex][3] == EMPTY &&
					colors[castleIndex][1] == EMPTY && colors[castleIndex][2] == EMPTY && colors[castleIndex][3] == EMPTY))
			{
				blueRectangles[castleIndex][2] = BLUE_RECTANGLE;
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

bool King::checkIfCheckmate(int board[][8], char colors[][8], char whiteColorsSquares[][8], char blackColorsSquares[][8])
{
	bool kingHaveSquare = false;
	bool piecePreventCheckmate = false;
	if (check)
	{
		char boardToCheck[HEIGHT][WIDTH];
		if (colors[kingRow][kingColumn] == WHITE) 
			assignArray(boardToCheck, whiteColorsSquares);
		else 
			assignArray(boardToCheck, whiteColorsSquares);

		// Check if there are some blue rectangles for king available
		int moves[][2] = 
		{
			{-1, -1}, {-1, 0}, {-1, 1},
			{0, -1},           {0, 1},
			{1, -1}, {1, 0}, {1, 1}
		};

		// Check each possible move
		for (int i = 0; i < 8; ++i) 
		{
			int newRow = kingRow + moves[i][0];
			int newCol = kingColumn + moves[i][1];

			// Check if the king can move to the new position
			if (canMoveTo(board, blackColorsSquares, newRow, newCol)) 
				kingHaveSquare = true;
		}

		// Check if we can move some other piece than king to prevent the checkmate
		if (!kingHaveSquare && !piecePreventCheckmate)
			return true;
	}
	return false;
}

// Helper function
void King::assignArray(char boardTocheck[][8], char colorsSquares[][8])
{
	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j) {
			boardTocheck[i][j] = colorsSquares[i][j];
		}
	}
}

bool King::canMoveTo(int board[][8], char occupiedSquares[][8], int row, int col) 
{
	if (isValidSquare(row, col) && board[row][col] == NONE)
	{
		return occupiedSquares[row][col] == EMPTY;
	}
	return false;
}