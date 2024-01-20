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
	if (colors[fromRow][fromCol] == WHITE)
		updateRectangles(BLACK, fromRow, fromCol, board, colors, blueRectangles, forChecks);
	if (colors[fromRow][fromCol] == BLACK)
		updateRectangles(WHITE, fromRow, fromCol, board, colors, blueRectangles, forChecks);
}

void Knight::updateRectangles(char color, int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8], bool forChecks)
{
    const int moves[][2] = 
    {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {-1, 2}, {1, -2}, {-1, -2}
    };

    for (int i = 0; i < 8; ++i) {
        int newRow = fromRow + moves[i][0];
        int newCol = fromCol + moves[i][1];

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8 &&
            (colors[newRow][newCol] == EMPTY || colors[newRow][newCol] == color ||
                (forChecks && colors[fromRow][fromCol] != color))) {
            blueRectangles[newRow][newCol] = BLUE_RECTANGLE;
        }
    }
}