#include "knight.h"
#include "game.h"
#include <iostream>

Knight::Knight(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c)
	: Piece(filename, ren, bRow, bCol, c) {}

Knight::~Knight() {}

bool Knight::move(int toRow, int toCol, char blueRectangles[][8])
{
	return blueRectangles[toRow][toCol] == BLUE_RECTANGLE;
}

void Knight::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8], bool forChecks)
{
	std::cout << static_cast<char>(colors[fromRow][fromCol]) << std::endl;
	std::cout << "Coordinates : " << fromRow << " " << fromCol << std::endl;
	if (colors[fromRow][fromCol] == WHITE)
		updateRectangles(BLACK, fromRow, fromCol, board, colors, blueRectangles, forChecks);
	if (colors[fromRow][fromCol] == BLACK)
		updateRectangles(WHITE, fromRow, fromCol, board, colors, blueRectangles, forChecks);
}

void Knight::updateRectangles(char color, int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8], bool forChecks)
{
	// top right
	if (fromCol + 1 < 8 && fromRow + 2 < 8 && (colors[fromRow + 2][fromCol + 1] == EMPTY || colors[fromRow + 2][fromCol + 1] == color
		|| forChecks && colors[fromRow][fromCol] != color))
		blueRectangles[fromRow + 2][fromCol + 1] = BLUE_RECTANGLE;

	// top left
	if (fromCol - 1 >= 0 && fromRow + 2 < 8 && (colors[fromRow + 2][fromCol - 1] == EMPTY || colors[fromRow + 2][fromCol - 1] == color
		|| forChecks && colors[fromRow][fromCol] != color))
		blueRectangles[fromRow + 2][fromCol - 1] = BLUE_RECTANGLE;

	// bottom right
	if (fromCol + 1 < 8 && fromRow - 2 >= 0 && (colors[fromRow - 2][fromCol + 1] == EMPTY || colors[fromRow - 2][fromCol + 1] == color
		|| forChecks && colors[fromRow][fromCol] != color))
		blueRectangles[fromRow - 2][fromCol + 1] = BLUE_RECTANGLE;

	// bottom left
	if (fromCol - 1 >= 0 && fromRow - 2 >= 0 && (colors[fromRow - 2][fromCol - 1] == EMPTY || colors[fromRow - 2][fromCol - 1] == color
		|| forChecks && colors[fromRow][fromCol] != color))
		blueRectangles[fromRow - 2][fromCol - 1] = BLUE_RECTANGLE;

	// right top
	if (fromCol + 2 < 8 && fromRow - 1 >= 0 && (colors[fromRow - 1][fromCol + 2] == EMPTY || colors[fromRow - 1][fromCol + 2] == color
		|| forChecks && colors[fromRow][fromCol] != color))
		blueRectangles[fromRow - 1][fromCol + 2] = BLUE_RECTANGLE;

	// right bottom
	if (fromCol + 2 < 8 && fromRow + 1 < 8 && (colors[fromRow + 1][fromCol + 2] == EMPTY || colors[fromRow + 1][fromCol + 2] == color
		|| forChecks && colors[fromRow][fromCol] != color))
		blueRectangles[fromRow + 1][fromCol + 2] = BLUE_RECTANGLE;

	// left top
	if (fromCol - 2 >= 0 && fromRow + 1 < 8 && (colors[fromRow + 1][fromCol - 2] == EMPTY || colors[fromRow + 1][fromCol - 2] == color
		|| forChecks && colors[fromRow][fromCol] != color))
		blueRectangles[fromRow + 1][fromCol - 2] = BLUE_RECTANGLE;

	// left bottom
	if (fromCol - 2 >= 0 && fromRow - 1 >= 0 && (colors[fromRow - 1][fromCol - 2] == EMPTY || colors[fromRow - 1][fromCol - 2] == color
		|| forChecks && colors[fromRow][fromCol] != color))
		blueRectangles[fromRow - 1][fromCol - 2] = BLUE_RECTANGLE;
}