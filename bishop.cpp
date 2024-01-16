#include "bishop.h"
#include "game.h"

Bishop::Bishop(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c)
	: Piece(filename, ren, bRow, bCol, c) {}

Bishop::~Bishop() {}

bool Bishop::move(int toRow, int toCol, char blueRectangles[][8])
{
	return blueRectangles[toRow][toCol] == BLUE_RECTANGLE;
}

void Bishop::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8], bool forChecks)
{
	if (colors[fromRow][fromCol] == WHITE)
		updateRectangles(WHITE, fromRow, fromCol, board, colors, blueRectangles, forChecks);
	else if (colors[fromRow][fromCol] == BLACK)
		updateRectangles(BLACK, fromRow, fromCol, board, colors, blueRectangles, forChecks);
}

void Bishop::updateRectangles(char color, int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8], bool forChecks)
{
    // Define the possible directions for diagonal moves
    int directions[4][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

    for (size_t d = 0; d < 4; d++) 
    {
        int dirRow = directions[d][0];
        int dirCol = directions[d][1];

        for (size_t step = 1; step < 8; step++) {
            int toRow = fromRow + step * dirRow;
            int toCol = fromCol + step * dirCol;

            // Check if the position is within the bounds of the chessboard
            if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8) 
            {
                if (colors[toRow][toCol] == EMPTY || colors[toRow][toCol] != color || (forChecks && colors[toRow][toCol] == color))
                    blueRectangles[toRow][toCol] = BLUE_RECTANGLE;

                // Stop further moves if the position is not empty
                if (colors[toRow][toCol] != EMPTY)
                    break;
            }
            // Stop when going out of the board
            else 
                break;
        }
    }
}