#include "board.h"
#include "textureManager.h"

Board::Board(const char* filename, SDL_Renderer* ren)
{
	renderer = ren;
	boardTexture = TextureManager::LoadTexture(filename, renderer);

	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			if (i > 1 && i < 6)
			{
				colors[i][j] = EMPTY;
				board[i][j] = NONE;
			}
			else if (i <= 1)
				colors[i][j] = WHITE;
			else if (i >= 6)
				colors[i][j] = BLACK;

			if (i == 1 || i == 6)
			{
				board[i][j] == PAWN;
			}
			if (i == 0 || i == 7)
			{
				if (j == 0 || j == 7)
					board[i][j] = ROOK;
				else if (j == 1 || j == 6)
					board[i][j] = KNIGHT;
				else if (j == 2 || j == 5)
					board[i][j] == BISHOP;
				else if (j == 3)
					board[i][j] = KING;
				else if (j == 4);
					board[i][j] = QUENN;
			} 
		}
	}

	
}

Board::~Board() {}

void Board::render()
{
	// Render the board
	SDL_RenderCopy(renderer, boardTexture, NULL, NULL);
	// Render all the pieces
	
}