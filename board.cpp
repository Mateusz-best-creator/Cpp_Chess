#include "board.h"
#include "textureManager.h"
#include <cstring>

Board::Board(const char* filename, SDL_Renderer* ren)
{
	renderer = ren;
	boardTexture = TextureManager::LoadTexture(filename, renderer);

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
				if (colors[i][j] == 'w') 
					pieces.push_back(std::make_unique<Pawn>
						("ChessPieces/Chess_plt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'w'));
				else
					pieces.push_back(std::make_unique<Pawn>
						("ChessPieces/Chess_pdt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'b'));
				break;
			case ROOK:
				if (colors[i][j] == 'w')
					pieces.push_back(std::make_unique<Rook>
						("ChessPieces/Chess_rlt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'w'));
				else
					pieces.push_back(std::make_unique<Rook>
						("ChessPieces/Chess_rdt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'b'));
				break;
			case KNIGHT:
				if (colors[i][j] == 'w')
					pieces.push_back(std::make_unique<Knight>
						("ChessPieces/Chess_nlt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'w'));
				else
					pieces.push_back(std::make_unique<Knight>
						("ChessPieces/Chess_ndt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'b'));
				break;
			case BISHOP:
				if (colors[i][j] == 'w')
					pieces.push_back(std::make_unique<Bishop>
						("ChessPieces/Chess_blt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'w'));
				else
					pieces.push_back(std::make_unique<Bishop>
						("ChessPieces/Chess_bdt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'b'));
				break;
			case KING:
				if (colors[i][j] == 'w')
					pieces.push_back(std::make_unique<King>
						("ChessPieces/Chess_klt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'w'));
				else
					pieces.push_back(std::make_unique<King>
						("ChessPieces/Chess_kdt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'b'));
				break;
			case QUEEN:
				if (colors[i][j] == 'w')
					pieces.push_back(std::make_unique<Queen>
						("ChessPieces/Chess_qlt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'w'));
				else
					pieces.push_back(std::make_unique<Queen>
						("ChessPieces/Chess_qdt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'b'));
				break;
			}
		}
	}
}

Board::~Board() {}

void Board::update()
{
	for (size_t i = 0; i < pieces.size(); i++)
	{
		pieces[i]->update();
	}
}

void Board::render()
{
	// Render the board
	SDL_RenderCopy(renderer, boardTexture, NULL, NULL);

	// Render all the pieces
	for (size_t i = 0; i < pieces.size(); i++)
		pieces[i]->render();
}