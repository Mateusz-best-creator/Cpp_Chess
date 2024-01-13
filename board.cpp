#include "board.h"
#include "textureManager.h"
#include <cstring>

Board::Board(const char* filename, SDL_Renderer* ren)
{
	renderer = ren;
	boardTexture = TextureManager::LoadTexture(filename, renderer);
	blueRectangleTexture = TextureManager::LoadTexture("ChesPieces/blue.png", renderer);

	int boardR = 0;

	for (int i = 0; i < HEIGHT; i++)
	{
		// Get current row on board
		boardR = 8 - i;

		for (int j = 0; j < WIDTH; j++)
		{
			rectangles.push_back(std::make_unique<BlueRectangle>("ChessPieces/blue.png", renderer, boardR, j+1));

			if (colors[i][j] == 'e')
				continue;
			char filename[30];
			switch (board[i][j]) 
			{
			case PAWN:

				if (colors[i][j] == 'w')
					pieces.push_back(std::make_unique<Pawn>
						("ChessPieces/Chess_plt60.png", renderer, boardR, j + 1, 'w'));
				else
					pieces.push_back(std::make_unique<Pawn>
						("ChessPieces/Chess_pdt60.png", renderer, boardR, j + 1, 'b'));
				break;
			case ROOK:
				/*
				if (colors[i][j] == 'w')
					pieces.push_back(std::make_unique<Rook>
						("ChessPieces/Chess_rlt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'w'));
				else
					pieces.push_back(std::make_unique<Rook>
						("ChessPieces/Chess_rdt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'b'));
						*/
				break;
			case KNIGHT:
				/*
				if (colors[i][j] == 'w')
					pieces.push_back(std::make_unique<Knight>
						("ChessPieces/Chess_nlt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'w'));
				else
					pieces.push_back(std::make_unique<Knight>
						("ChessPieces/Chess_ndt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'b'));
						*/
				break;
			case BISHOP:
				/*
				if (colors[i][j] == 'w')
					pieces.push_back(std::make_unique<Bishop>
						("ChessPieces/Chess_blt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'w'));
				else
					pieces.push_back(std::make_unique<Bishop>
						("ChessPieces/Chess_bdt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'b'));
						*/
				break;
			case KING:
				/*
				if (colors[i][j] == 'w')
					pieces.push_back(std::make_unique<King>
						("ChessPieces/Chess_klt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'w'));
				else
					pieces.push_back(std::make_unique<King>
						("ChessPieces/Chess_kdt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'b'));
						*/
				break;
			case QUEEN:
				/*
				if (colors[i][j] == 'w')
					pieces.push_back(std::make_unique<Queen>
						("ChessPieces/Chess_qlt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'w'));
				else
					pieces.push_back(std::make_unique<Queen>
						("ChessPieces/Chess_qdt60.png", renderer, 53 + j * PIECES_X_DISTANCE, 35 + i * PIECES_Y_DISTANCE, 1, 'b'));
						*/
				break;
			}
		}
	}
}

Board::~Board() {}

void Board::update()
{
	sourceRect.h = 600;
	sourceRect.w = 800;
	sourceRect.x = 0;
	sourceRect.y = 0;

	destinationRect.x = 0;
	destinationRect.y = 0;
	destinationRect.w = sourceRect.w;
	destinationRect.h = sourceRect.h;
	for (size_t i = 0; i < pieces.size(); i++)
	{
		pieces[i]->update();
	}

	int counter = 0;
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (blueRectanglesBoard[i][j] != 'e')
				rectangles[counter]->update();
			counter++;
		}
	}
}

void Board::render()
{
	// Render the board
	SDL_RenderCopy(renderer, boardTexture, &sourceRect, &destinationRect);

	// Render all the pieces
	for (size_t i = 0; i < pieces.size(); i++)
		pieces[i]->render();
	int counter = 0;
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (blueRectanglesBoard[i][j] != 'e')
				rectangles[counter]->render();
			counter++;
		}
	}
}

void Board::choosingPiece(int row, int column)
{
	int pieceType = board[row][column];
	if (pieceType == NONE)
		return;

	switch (pieceType)
	{
	case PAWN:
		if (colors[row][column] == 'w')
		{

		}
		else
		{

		}
		break;
	default:
		break;
	}
}