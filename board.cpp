#include "board.h"
#include "textureManager.h"
#include <cstring>

Board::Board(const char* filename, SDL_Renderer* ren)
{
	renderer = ren;
	boardTexture = TextureManager::LoadTexture(filename, renderer);

	int index = 0;
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			if (colors[i][j] == 'e')
				continue;
			char filename[30];

			switch (board[i][j]) 
			{
			case PAWN:
				if (colors[i][j] == 'w') strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_plt60.png");
				else strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_pdt60.png");
				break;
			case ROOK:
				if (colors[i][j] == 'w') strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_rlt60.png");
				else strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_rdt60.png");
				break;
			case KNIGHT:
				if (colors[i][j] == 'w') strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_nlt60.png");
				else strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_ndt60.png");
				break;
			case BISHOP:
				if (colors[i][j] == 'w') strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_blt60.png");
				else strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_bdt60.png");
				break;
			case KING:
				if (colors[i][j] == 'w') strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_klt60.png");
				else strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_kdt60.png");
				break;
			case QUEEN:
				if (colors[i][j] == 'w') strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_qlt60.png");
				else strcpy_s(filename, sizeof(filename), "ChessPieces/Chess_qdt60.png");
				break;
			}
			pieces[index] = new Piece(filename, renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE);
			index++;
		}
	}
	std::cout << "INDEX: " << index << std::endl;
}

Board::~Board() 
{
	for (size_t i = 0; i < INITIAL_PIECES_NUMBER; i++);
		//delete pieces[i];
}

void Board::update()
{
	for (size_t i = 0; i < INITIAL_PIECES_NUMBER; i++)
	{
		pieces[i]->update();
	}
}

void Board::render()
{
	// Render the board
	SDL_RenderCopy(renderer, boardTexture, NULL, NULL);

	// Render all the pieces
	for (size_t i = 0; i < INITIAL_PIECES_NUMBER; i++)
		pieces[i]->render();
}