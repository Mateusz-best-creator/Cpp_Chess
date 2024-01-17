#include "board.h"
#include <typeinfo>

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