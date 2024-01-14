#include "rook.h"
#include "game.h"
#include <iostream>

Rook::Rook(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c)
	: Piece(filename, ren, bRow, bCol, c)
{}

Rook::~Rook() {}

bool Rook::move(int toRow, int toCol, char blueRectangles[][8])
{
	return blueRectangles[toRow][toCol] == BLUE_RECTANGLE;
}

void Rook::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8])
{
	std::cout << fromRow << " " << fromCol << std::endl;
	if (colors[fromRow][fromCol] == WHITE)
	{
		size_t i;
		for (i = fromRow + 1; i < 8; i++)
		{
			if (colors[i][fromCol] == EMPTY)
				blueRectangles[i][fromCol] = BLUE_RECTANGLE;
			else if (colors[i][fromCol] == BLACK)
			{
				blueRectangles[i][fromCol] = BLUE_RECTANGLE;
				break;
			}
			else
				break;
		}
		for (i = fromRow - 1; i >= 0; i--)
		{
			if (colors[i][fromCol] == EMPTY)
				blueRectangles[i][fromCol] = BLUE_RECTANGLE;
			else if (colors[i][fromCol] == BLACK)
			{
				blueRectangles[i][fromCol] = BLUE_RECTANGLE;
				break;
			}
			else
				break;
		}

		// Left and right checks
		for (i = fromCol + 1; i < 8; i++)
		{	
			if (colors[fromRow][i] == EMPTY)
				blueRectangles[fromRow][i] = BLUE_RECTANGLE;
			else if (colors[fromRow][i] == BLACK)
			{
				blueRectangles[fromRow][i] = BLUE_RECTANGLE;
				break;
			}
			else
				break;
		}
		for (i = fromCol - 1; i >= 0; i--)
		{
			if (colors[fromRow][i] == EMPTY)
				blueRectangles[fromRow][i] = BLUE_RECTANGLE;
			else if (colors[fromRow][i] == BLACK)
			{
				blueRectangles[fromRow][i] = BLUE_RECTANGLE;
				break;
			}
			else
				break;
		}
	}
	else if (colors[fromRow][fromCol] == BLACK)
	{

	}
}