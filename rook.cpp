#include "rook.h"
#include "game.h"

Rook::Rook(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c)
	: Piece(filename, ren, bRow, bCol, c)
{}

Rook::~Rook() {}

bool Rook::move(int toRow, int toCol, char blueRectangles[][8])
{
	return blueRectangles[toRow][toCol] == BLUE_RECTANGLE;
}

void Rook::displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8], bool forChecks)
{
	if (colors[fromRow][fromCol] == WHITE)
		updateRectangles(WHITE, fromRow, fromCol, board, colors, blueRectangles, forChecks);
	else if (colors[fromRow][fromCol] == BLACK)
		updateRectangles(BLACK, fromRow, fromCol, board, colors, blueRectangles, forChecks);
}

void Rook::updateRectangles(char color, int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8], bool forChecks)
{
    int directions[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    char enemyColor;

    for (int d = 0; d < 4; ++d) {
        int dirRow = directions[d][0];
        int dirCol = directions[d][1];

        for (int step = 1; step < 8; ++step) 
        {
            int toRow = fromRow + step * dirRow;
            int toCol = fromCol + step * dirCol;
            enemyColor = colors[fromRow][fromCol] == WHITE ? BLACK : WHITE;

            // Check if the position is within the bounds of the chessboard
            if (toRow >= 0 && toRow < 8 && toCol >= 0 && toCol < 8) 
            {
                // Check if the position is empty or has an opponent's piece
                if (colors[toRow][toCol] == EMPTY || colors[toRow][toCol] != color || (forChecks && colors[toRow][toCol] == color))
                    blueRectangles[toRow][toCol] = BLUE_RECTANGLE;

                // Stop further moves if the position is not empty
                if (colors[toRow][toCol] != EMPTY)
                {
                    if (colors[toRow][toCol] == enemyColor && board[toRow][toCol] == KING)
                        continue;
                    break;
                }
            }
            else
                break;
        }
    }
}