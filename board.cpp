#include "board.h"
#include "textureManager.h"
#include <cstring>

Board::Board(const char* filename, SDL_Renderer* ren)
{
	renderer = ren;
	boardTexture = TextureManager::LoadTexture(filename, renderer);
	blueRectangleTexture = TextureManager::LoadTexture("ChesPieces/blue.png", renderer);
	movingPieceType = NONE;

	int boardR = 0;
	pieces.clear();
	rectangles.clear();

	for (int i = 0; i < HEIGHT; i++)
	{
		// Get current row on board
		boardR = 8 - i;

		for (int j = 0; j < WIDTH; j++)
		{
			rectangles.push_back(std::make_unique<BlueRectangle>("ChessPieces/blue.png", renderer, i + 1, j + 1));

			if (colors[i][j] == 'e')
				continue;
			addPieces(i, j, boardR);
		}
	}
	fromRow = fromCol = toRow = toCol = -1;
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

	pieces.clear();
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (board[i][j] == NONE)
				continue;
			addPieces(i, j, 8 - i);
		}
	}

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
			{
				rectangles[counter]->update();
			}
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
			{
				rectangles[counter]->render();
			}
			counter++;
		}
	}
}

void Board::addPieces(int i, int j, int boardR)
{
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

void Board::movingPiece(int row, int column, int& playerIndex)
{
	// Subtract one beacuse arrays are indexes from 0 (rows and cols from 1)
	row--;
	column--;
	if (board[row][column] == NONE && (toRow != INITIAL_VALUE && toCol != INITIAL_VALUE))
		return;
	else if (fromRow == INITIAL_VALUE && fromCol == INITIAL_VALUE)
		movingPieceType = board[row][column];
	if (movingPieceType == NONE)
		return;

	if (fromRow == INITIAL_VALUE && fromCol == INITIAL_VALUE)
	{
		fromRow = row;
		fromCol = column;
		// Display blue rectangles
		return;
	}
	else
	{
		toRow = row;
		toCol = column;
	}

	if (fromRow < 0 || toRow < 0 || fromRow > 7 || toCol > 7)
		throw InvalidIndexException(fromRow, fromCol, toRow, toCol);

	if (colors[fromRow][fromCol] == 'w' && playerIndex == 2)
	{
		fromRow = fromCol = toRow = toCol = INITIAL_VALUE;
		return;
	}
	else if (colors[fromRow][fromCol] == 'b' && playerIndex == 1)
	{
		fromRow = fromCol = toRow = toCol = INITIAL_VALUE;
		return;
	}

	switch (movingPieceType)
	{
	case PAWN:
		// Check if the move from fromRow, fromCol to toRow, toCol is valid for a pawn
		for (size_t i = 0; i < pieces.size(); i++)
		{
			Pawn* ptr;
			if (ptr = dynamic_cast<Pawn*>(pieces[i].get()))
			{
				if (!ptr->move(fromRow, fromCol, toRow, toCol, board, colors))
				{
					std::cout << "You cant move from " << fromRow << ", " << fromCol << " to " << toRow << ", " << toCol << std::endl;
					fromRow = fromCol = toRow = toCol = INITIAL_VALUE;
					return;
				}
				else
					break;
			}
		}
		board[fromRow][fromCol] = NONE;
		board[toRow][toCol] = PAWN;

		if (colors[fromRow][fromCol] == 'w') // white
		{
			colors[fromRow][fromCol] = 'e';
			colors[toRow][toCol] = 'w';
		}

		else if (colors[fromRow][fromCol] == 'b') // black
		{
			colors[fromRow][fromCol] = 'e';
			colors[toRow][toCol] = 'b';
		}

		break;
	default:
		break;
	}
	fromRow = fromCol = toRow = toCol = INITIAL_VALUE;
	playerIndex = (playerIndex == 1) ? 2 : 1;
}