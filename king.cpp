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
		bool isValidShortCastle = true;
		for (int i = 5; i <= 6; i++) 
		{
			if ((blackColorsSquares[castleIndex][i] != EMPTY || colors[castleIndex][i] != EMPTY) &&
				(whiteColorsSquares[castleIndex][i] != EMPTY || colors[castleIndex][i] != EMPTY)) 
			{
				isValidShortCastle = false;
				break;
			}
		}
		if (!shortCastleRookMoved && isValidShortCastle)
			blueRectangles[castleIndex][6] = BLUE_RECTANGLE;

		// Long castle
		if (!longCastleRookMoved)
		{
			bool isValidLongCastle = true;
			for (int i = 1; i <= 3; i++) 
			{
				if ((blackColorsSquares[castleIndex][i] != EMPTY || colors[castleIndex][i] != EMPTY) &&
					(whiteColorsSquares[castleIndex][i] != EMPTY || colors[castleIndex][i] != EMPTY)) 
				{
					isValidLongCastle = false;
					break;
				}
			}
			if (!longCastleRookMoved && isValidLongCastle) 
				blueRectangles[castleIndex][2] = BLUE_RECTANGLE;
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
	check = boardToCheck[kingRow][kingColumn] != EMPTY;
	return check;
}

bool King::checkIfKingHasSquare(int board[][8], char colors[][8], char whiteColorsSquares[][8], char blackColorsSquares[][8])
{
	bool kingHaveSquare = false;
	if (check)
	{
		char boardToCheck[HEIGHT][WIDTH];
		if (colors[kingRow][kingColumn] == WHITE)
			assignArray(boardToCheck, blackColorsSquares);
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
		for (int i = 0; i < 8; i++)
		{
			int newRow = kingRow + moves[i][0];
			int newCol = kingColumn + moves[i][1];

			// Check if the king can move to the new position
			if (canMoveTo(colors, boardToCheck, newRow, newCol))
			{
				std::cout << "King can move to: " << newRow << " " << newCol << std::endl;
				kingHaveSquare = true;
			}
		}
		if (!kingHaveSquare)
			return true;
	}
	return false;
}

// Helper function
void King::assignArray(char boardTocheck[][8], char colorsSquares[][8])
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++) {
			boardTocheck[i][j] = colorsSquares[i][j];
		}
	}
}

bool King::canMoveTo(char colors[][8], char occupiedSquares[][8], int row, int col)
{
	char enemyColor = colors[kingRow][kingColumn] == WHITE ? BLACK : WHITE;
	if (isValidSquare(row, col) && (colors[row][col] == enemyColor || colors[row][col] == EMPTY))
		return occupiedSquares[row][col] == EMPTY;
	return false;
}

void King::performShortCastle(int row, int column, int board[][8], char colors[][8])
{
	board[row][column + 1] = NONE;
	board[row][column - 1] = ROOK;
	colors[row][column + 1] = EMPTY;
	colors[row][column - 1] = colors[row][column] = color;
	board[row][column] = KING;
	kingRow = row;
	kingColumn = column;
	shortCastleRookMoved = longCastleRookMoved = hasMoved = true;
}

void King::performLongCastle(int row, int column, int board[][8], char colors[][8])
{
	board[row][column] = KING;
	board[row][column + 1] = ROOK;
	colors[row][column + 1] = colors[row][column] = color;
	colors[row][column - 2] = EMPTY;
	board[row][column - 2] = NONE;
	kingRow = row;
	kingColumn = column;
	shortCastleRookMoved = longCastleRookMoved = hasMoved = true;
}