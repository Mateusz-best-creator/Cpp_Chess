#include "pawn.h"
#include "textureManager.h"
#include <iostream>

Pawn::Pawn(const char* filename, SDL_Renderer* ren, int bRow, int bColumn, char c)
	: Piece(filename, ren, bRow, bColumn, c)
{}

Pawn::~Pawn() {}

static int previousRow, previousCol;

bool Pawn::move(int toRow, int toCol, char blueRectangles[][8])
{
	return blueRectangles[toRow][toCol] == BLUE_RECTANGLE;
}

void Pawn::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char boardToUpdate[][8], bool forChecks)
{
    if (colors[fromRow][fromCol] == WHITE) {
        // White pawn moves
        if (fromRow + 2 < 8 && colors[fromRow + 2][fromCol] == EMPTY && fromRow == 1)
            boardToUpdate[fromRow + 2][fromCol] = BLUE_RECTANGLE;
        if (fromRow + 1 < 8 && colors[fromRow + 1][fromCol] == EMPTY)
            boardToUpdate[fromRow + 1][fromCol] = BLUE_RECTANGLE;
        if (fromRow + 1 < 8 && fromCol + 1 < 8 && colors[fromRow + 1][fromCol + 1] != EMPTY && colors[fromRow + 1][fromCol + 1] == BLACK)
            boardToUpdate[fromRow + 1][fromCol + 1] = BLUE_RECTANGLE;
        if (fromRow + 1 < 8 && fromCol - 1 >= 0 && colors[fromRow + 1][fromCol - 1] != EMPTY && colors[fromRow + 1][fromCol - 1] == BLACK)
            boardToUpdate[fromRow + 1][fromCol - 1] = BLUE_RECTANGLE;
    }
    else if (colors[fromRow][fromCol] == BLACK) {
        // Black pawn moves
        if (fromRow - 2 >= 0 && colors[fromRow - 2][fromCol] == EMPTY && fromRow == 6)
            boardToUpdate[fromRow - 2][fromCol] = BLUE_RECTANGLE;
        if (fromRow - 1 >= 0 && colors[fromRow - 1][fromCol] == EMPTY)
            boardToUpdate[fromRow - 1][fromCol] = BLUE_RECTANGLE;
        if (fromRow - 1 >= 0 && fromCol + 1 < 8 && colors[fromRow - 1][fromCol + 1] != EMPTY && colors[fromRow - 1][fromCol + 1] == WHITE)
            boardToUpdate[fromRow - 1][fromCol + 1] = BLUE_RECTANGLE;
        if (fromRow - 1 >= 0 && fromCol - 1 >= 0 && colors[fromRow - 1][fromCol - 1] != EMPTY && colors[fromRow - 1][fromCol - 1] == WHITE)
            boardToUpdate[fromRow - 1][fromCol - 1] = BLUE_RECTANGLE;
    }

}

