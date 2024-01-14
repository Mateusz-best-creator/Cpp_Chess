#include "rook.h"
#include <iostream>
Rook::Rook(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c)
	: Piece(filename, ren, bRow, bCol, c)
{}

Rook::~Rook() {}

bool Rook::move(int fromRow, int fromCol, int toRow, int toCol, int board[][8], char colors[][8])
{
	return true;
}

void Rook::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8])
{
	std::cout << "HALOO" << std::endl;
	if (colors[fromRow][fromCol] == 'w')
	{
		// Upper and lower checks
		for (size_t i = fromRow + 1; i < 8; i++)
		{
			if (colors[i][fromCol] == 'e' || colors[i][fromCol] == 'b')
			{
				blueRectangles[fromRow][i] = 'b';
				break;
			}
		}
		for (size_t i = fromRow - 1; i >= 0; i--)
		{
			if (colors[i][fromCol] == 'e' || colors[i][fromCol] == 'b')
			{
				blueRectangles[i][fromCol] = 'b';
				break;
			}
		}
		// Left and right checks
		for (size_t i = fromCol + 1; i < 8; i++)
		{
			if (colors[fromRow][i] == 'e' || colors[fromRow][i] == 'b')
			{
				blueRectangles[fromRow][i] = 'b';
				break;
			}
		}
		for (size_t i = fromCol - 1; i >= 0; i--)
		{
			if (colors[fromRow][i] == 'e' || colors[fromRow][i] == 'b')
			{
				blueRectangles[fromRow][i] = 'b';
				break;
			}
		}
	}
	
}