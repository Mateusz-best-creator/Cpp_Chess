#include "board.h"
#include "textureManager.h"
#include <cstring>
#include <typeinfo>
#include <iostream>

// Helper function
void Board::resetBlueRectanglesBoard()
{
	// Reset blue rectangles
	for (size_t i = 0; i < HEIGHT; i++)
		for (size_t j = 0; j < WIDTH; j++)
			blueRectanglesBoard[i][j] = EMPTY;
}

Board::Board(const char* filename, SDL_Renderer* ren)
{
	renderer = ren;
	boardTexture = TextureManager::LoadTexture(filename, renderer);
	movingPieceType = NONE;
	redRectangle = std::make_unique<BlueRectangle>("ChessPieces/red.png", renderer, 1, 1);

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

			if (colors[i][j] == EMPTY)
				continue;
			addPieces(i, j, boardR);
		}
	}
	fromRow = fromCol = toRow = toCol = -1;
	// Create seperate instance of each pawn for simplicity
	pawn = std::make_shared<Pawn>("ChessPieces/Chess_plt60.png", renderer, 1, 1, WHITE);
	rook = std::make_shared<Rook>("ChessPieces/Chess_rlt60.png", renderer, 1, 1, WHITE);
	knight = std::make_shared<Knight>("ChessPieces/Chess_ndt60.png", renderer, 1, 1, WHITE);
	bishop = std::make_shared<Bishop>("ChessPieces/Chess_ndt60.png", renderer, 1, 1, WHITE);
	queen = std::make_shared<Queen>("ChessPieces/Chess_ndt60.png", renderer, 1, 1, WHITE);
	whiteKing = std::make_shared<King>("ChessPieces/Chess_ndt60.png", renderer, 1, 1, WHITE);
	blackKing = std::make_shared<King>("ChessPieces/Chess_ndt60.png", renderer, 1, 1, BLACK);
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
	int counter = 0;
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (blueRectanglesBoard[i][j] != EMPTY)
				rectangles[counter]->update();
			counter++;
		}
	}
	
	for (size_t i = 0; i < pieces.size(); i++)
		pieces[i]->update();

	if (whiteKing->getCheck())
	{
		redRectangle->getBoardRow() = whiteKing->getKingRow() + 1; // We add 1 beacuse we index from 0
		redRectangle->getBoardcolumn() = whiteKing->getKingColumn() + 1;
		redRectangle->update();
	}
	else if (blackKing->getCheck())
	{
		redRectangle->getBoardRow() = blackKing->getKingRow() + 1; // We add 1 beacuse we index from 0
		redRectangle->getBoardcolumn() = blackKing->getKingColumn() + 1;
		redRectangle->update();
	}
}

void Board::render()
{
	// Render the board
	SDL_RenderCopy(renderer, boardTexture, &sourceRect, &destinationRect);
	
	// Render all blue rectangles
	int counter = 0;
	for (size_t i = 0; i < HEIGHT; i++)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (blueRectanglesBoard[i][j] != EMPTY)
			{
				rectangles[counter]->render();
			}
			counter++;
		}
	}
	// Render red rectangle if there is a check
	if (whiteKing->getCheck() || blackKing->getCheck())
		redRectangle->render();

	// Render all the pieces
	for (size_t i = 0; i < pieces.size(); i++)
		pieces[i]->render();
}

void Board::addPieces(int i, int j, int boardR)
{
	switch (board[i][j])
	{
	case PAWN:

		if (colors[i][j] == WHITE)
			pieces.push_back(std::make_shared<Pawn>
				("ChessPieces/Chess_plt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<Pawn>
				("ChessPieces/Chess_pdt60.png", renderer, boardR, j + 1, BLACK));
		break;
	case ROOK:
		if (colors[i][j] == WHITE)
			pieces.push_back(std::make_shared<Rook>
				("ChessPieces/Chess_rlt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<Rook>
				("ChessPieces/Chess_rdt60.png", renderer, boardR, j + 1, BLACK));
		break;
	case KNIGHT:
		if (colors[i][j] == WHITE)
			pieces.push_back(std::make_shared<Knight>
				("ChessPieces/Chess_nlt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<Knight>
				("ChessPieces/Chess_ndt60.png", renderer, boardR, j + 1, BLACK));
		break;
	case BISHOP:
		if (colors[i][j] == WHITE)
			pieces.push_back(std::make_shared<Bishop>
				("ChessPieces/Chess_blt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<Bishop>
				("ChessPieces/Chess_bdt60.png", renderer, boardR, j + 1, BLACK));
		break;
	case QUEEN:
		if (colors[i][j] == WHITE)
			pieces.push_back(std::make_shared<Queen>
				("ChessPieces/Chess_qlt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<Queen>
				("ChessPieces/Chess_qdt60.png", renderer, boardR, j + 1, BLACK));
		break;
	case KING:
		if (colors[i][j] == 'w')
			pieces.push_back(std::make_shared<King>
				("ChessPieces/Chess_klt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<King>
				("ChessPieces/Chess_kdt60.png", renderer, boardR, j + 1, BLACK));
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

	if (fromRow == INITIAL_VALUE && fromCol == INITIAL_VALUE)
	{
		movingPieceType = board[row][column];
		if (movingPieceType == NONE)
			return;
		fromRow = row;
		fromCol = column;
		switch (board[fromRow][fromCol])
		{
		case PAWN:
			pawn->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false);
			break;
		case ROOK:
			rook->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false);
			break;
		case KNIGHT:
			knight->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false);
			break;
		case BISHOP:
			bishop->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false);
			break;
		case QUEEN:
			queen->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false);
			break;
		case KING:
			whiteKing->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false, whiteSquaresBoard, blackSquaresBoard);
		}
		return;
	}
	else
	{
		toRow = row;
		toCol = column;
	}

	// Check if index is valid
	if (fromRow < 0 || toRow < 0 || fromRow > 7 || toCol > 7)
		throw InvalidIndexException(fromRow, fromCol, toRow, toCol);

	// Check if it is player's turn
	if ((colors[fromRow][fromCol] == WHITE && playerIndex == 2) || (colors[fromRow][fromCol] == BLACK && playerIndex == 1))
	{
		fromRow = fromCol = toRow = toCol = INITIAL_VALUE;
		resetBlueRectanglesBoard();
		return;
	}
	// Update all the pieces
	bool updated = updatePieces();
	resetBlueRectanglesBoard();
	// Reset variables
	fromRow = fromCol = toRow = toCol = INITIAL_VALUE;
	if (updated)
	{
		playerIndex = (playerIndex == 1) ? 2 : 1;
		updateColorsSquares();
	}


}

bool Board::updatePieces()
{
	switch (movingPieceType)
	{
	case PAWN:
		if (!updatePiece(pawn))
			return false;
		break;
	case ROOK:
		if (!updatePiece(rook))
			return false;
		break;
	case KNIGHT:
		if (!updatePiece(knight))
			return false;
		break;
	case BISHOP:
		if (!updatePiece(bishop))
			return false;
		break;
	case QUEEN:
		if (!updatePiece(queen))
			return false;
		break;
	case KING:
		if (colors[fromRow][fromCol] == WHITE)
		{
			if (!updatePiece(whiteKing))
				return false;
		}
		else if (colors[fromRow][fromCol] == BLACK)
		{
			if (!updatePiece(blackKing))
				return false;
		}
		break;
	default:
		break;
	}

	if (colors[fromRow][fromCol] == WHITE)
	{
		colors[fromRow][fromCol] = EMPTY;
		colors[toRow][toCol] = WHITE;
	}

	else if (colors[fromRow][fromCol] == BLACK)
	{
		colors[fromRow][fromCol] = EMPTY;
		colors[toRow][toCol] = BLACK;
	}
	return true;
}

bool Board::updatePiece(std::shared_ptr<Piece> piece)
{
	if (!piece->move(toRow, toCol, blueRectanglesBoard))
	{
		std::cout << "You cant move from " << fromRow << ", " << fromCol << " to " << toRow << ", " << toCol << " with " 
			<< typeid(*piece).name() << std::endl;
		fromRow = fromCol = toRow = toCol = INITIAL_VALUE;
		return false;
	}
	board[fromRow][fromCol] = NONE;
	if (typeid(Pawn) == typeid(*piece))
		board[toRow][toCol] = PAWN;
	else if (typeid(Rook) == typeid(*piece))
		board[toRow][toCol] = ROOK;
	else if (typeid(Knight) == typeid(*piece))
		board[toRow][toCol] = KNIGHT;
	else if (typeid(Bishop) == typeid(*piece))
		board[toRow][toCol] = BISHOP;
	else if (typeid(Queen) == typeid(*piece))
		board[toRow][toCol] = QUEEN;
	else if (typeid(King) == typeid(*piece))
		board[toRow][toCol] = KING;
	return true;
}


void Board::updateColorsSquares()
{
	// Reset both boards
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
			whiteSquaresBoard[i][j] = blackSquaresBoard[i][j] = EMPTY;
	
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = WIDTH - 1; j >= 0; j--)
		{
			switch (board[i][j])
			{
			case NONE:
				break;
			/*
				Updating possible occupied squares by pawns is a bit different 
				than for other pieces, we have to check diagonals. 
			*/
			case PAWN:
				if (colors[i][j] == WHITE) 
				{
					if (j - 1 >= 0 && i + 1 < 8)
						whiteSquaresBoard[i + 1][j - 1] = BLUE_RECTANGLE;
					if (j + 1 < 8 && i + 1 < 8)
						whiteSquaresBoard[i + 1][j + 1] = BLUE_RECTANGLE;
				}
				else if (colors[i][j] == BLACK) {
					if (j - 1 >= 0 && i - 1 >= 0)
						blackSquaresBoard[i - 1][j - 1] = BLUE_RECTANGLE;
					if (j + 1 < 8 && i - 1 >= 0)
						blackSquaresBoard[i - 1][j + 1] = BLUE_RECTANGLE;
				}
				break;
			case ROOK:
				if (colors[i][j] == WHITE)
					rook->displayBlueRectangles(i, j, board, colors, whiteSquaresBoard, true);
				else if (colors[i][j] == BLACK)
					rook->displayBlueRectangles(i, j, board, colors, blackSquaresBoard, true);
				break;
			case KNIGHT:
				if (colors[i][j] == WHITE)
					knight->displayBlueRectangles(i, j, board, colors, whiteSquaresBoard, true);
				else if (colors[i][j] == BLACK)
					knight->displayBlueRectangles(i, j, board, colors, blackSquaresBoard, true);
				break;
			case BISHOP:
				if (colors[i][j] == WHITE)
					bishop->displayBlueRectangles(i, j, board, colors, whiteSquaresBoard, true);
				else if (colors[i][j] == BLACK)
					bishop->displayBlueRectangles(i, j, board, colors, blackSquaresBoard, true);
				break;
			case QUEEN:
				if (colors[i][j] == WHITE)
					queen->displayBlueRectangles(i, j, board, colors, whiteSquaresBoard, true);
				else if (colors[i][j] == BLACK)
					queen->displayBlueRectangles(i, j, board, colors, blackSquaresBoard, true);
				break;
			case KING:
				if (colors[i][j] == WHITE)
					whiteKing->displayBlueRectangles(i, j, board, colors, whiteSquaresBoard, true, whiteSquaresBoard, blackSquaresBoard);
				else if (colors[i][j] == BLACK)
					blackKing->displayBlueRectangles(i, j, board, colors, blackSquaresBoard, true, whiteSquaresBoard, blackSquaresBoard);
				break;
			}
		}
	}
	// Check for checks
	whiteKing->getCheck() = whiteKing->checkIfCheck(blackSquaresBoard) ? true : false;
	blackKing->getCheck() = blackKing->checkIfCheck(whiteSquaresBoard) ? true : false;
}