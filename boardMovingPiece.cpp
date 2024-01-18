#include "board.h"
#include <typeinfo>

// Helper function
void Board::resetBlueRectanglesBoard()
{
	// Reset blue rectangles
	for (size_t i = 0; i < HEIGHT; i++)
		for (size_t j = 0; j < WIDTH; j++)
			blueRectanglesBoard[i][j] = EMPTY;
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
			if (colors[fromRow][fromCol] == WHITE)
				whiteKing->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false, whiteSquaresBoard, blackSquaresBoard);
			else if (colors[fromRow][fromCol] == BLACK)
				blackKing->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false, whiteSquaresBoard, blackSquaresBoard);
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

	// Reset blue rectangles board
	resetBlueRectanglesBoard();

	if (updated)
	{
		playerIndex = (playerIndex == 1) ? 2 : 1;
		updateColorsSquares();
	}
	// Reset variables
	fromRow = fromCol = toRow = toCol = INITIAL_VALUE;

	// Check for checkmate
	if (playerIndex == 1 && whiteKing->checkIfCheckmate(board, colors, whiteSquaresBoard, blackSquaresBoard))
	{
		gameRunning = false;
		std::cout << "Checkmate, black pieces won!\n";
		// Pause the program for 3 seconds
	}
	else if (playerIndex == 2 && blackKing->checkIfCheckmate(board, colors, whiteSquaresBoard, blackSquaresBoard))
	{
		gameRunning = false;
		std::cout << "Checkmate, white pieces won!\n";
		// Pause the program for 3 seconds
	}
}

bool Board::updatePieces()
{
	bool updatedValuesForPoisson = false;

	switch (movingPieceType)
	{
	case PAWN:
		if (!updatePiece(pawn))
			return false;
		pawn->enPassantMove(fromRow, fromCol, toRow, toCol, colors, board, blueRectanglesBoard);
		pawn->getPreviousRow() = fromRow;
		pawn->getCurrentCol() = toCol;
		pawn->getCurrentRow() = toRow;
		updatedValuesForPoisson = true;
		break;
	case ROOK:
		if (!updatePiece(rook))
			return false;
		else
		{
			// Update variables necessary for castle move
			if (fromRow == 0 && fromCol == 0)
				whiteKing->getLongCastleRookMoved() = true;
			else if (fromRow == 0 && fromCol == 7)
				whiteKing->getShortCastleRookMoved() = true;
			else if (fromRow == 7 && fromCol == 0)
				blackKing->getLongCastleRookMoved() = true;
			else if (fromRow == 7 && fromCol == 7)
				blackKing->getShortCastleRookMoved() = true;
		}
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
			// Short castle for white king
			if (!whiteKing->getHasMoved() && toCol == 6 && blueRectanglesBoard[0][6] == BLUE_RECTANGLE && !whiteKing->getShortCastleRookMoved())
			{
				board[0][7] = NONE;
				board[0][5] = ROOK;
				colors[0][7] = EMPTY;
				colors[0][5] = colors[0][6] = WHITE;
				board[0][6] = KING;
				whiteKing->getKingRow() = 0;
				whiteKing->getKingColumn() = 6;
				whiteKing->getShortCastleRookMoved() = whiteKing->getLongCastleRookMoved() = whiteKing->getHasMoved() = true;
				break;
			}
			// Long castle for white king
			else if (!whiteKing->getHasMoved() && toCol == 2 && blueRectanglesBoard[0][2] == BLUE_RECTANGLE && !whiteKing->getLongCastleRookMoved())
			{
				board[0][0] = NONE;
				board[0][2] = KING;
				board[0][3] = ROOK;
				colors[0][0] = EMPTY;
				colors[0][3] = colors[0][2] = WHITE;
				whiteKing->getKingRow() = 0;
				whiteKing->getKingColumn() = 2;
				whiteKing->getShortCastleRookMoved() = whiteKing->getLongCastleRookMoved() = whiteKing->getHasMoved() = true;
				break;
			}

			if (!updatePiece(whiteKing))
				return false;
				
		}
		else if (colors[fromRow][fromCol] == BLACK)
		{
			// Short castle for black king
			if (!blackKing->getHasMoved() && toCol == 6 && blueRectanglesBoard[7][6] == BLUE_RECTANGLE && !blackKing->getShortCastleRookMoved())
			{
				board[7][7] = NONE;
				board[7][5] = ROOK;
				colors[7][7] = EMPTY;
				colors[7][5] = colors[7][6] = BLACK;
				board[7][6] = KING;
				blackKing->getKingRow() = 7;
				blackKing->getKingColumn() = 6;
				blackKing->getShortCastleRookMoved() = blackKing->getLongCastleRookMoved() = blackKing->getHasMoved() = true;
				break;
			}
			// Long castle for black king
			else if (!blackKing->getHasMoved() && toCol == 2 && blueRectanglesBoard[7][2] == BLUE_RECTANGLE && !blackKing->getLongCastleRookMoved())
			{
				board[7][0] = NONE;
				board[7][2] = KING;
				board[7][3] = ROOK;
				colors[7][0] = EMPTY;
				colors[7][3] = colors[7][2] = BLACK;
				blackKing->getKingRow() = 7;
				blackKing->getKingColumn() = 2;
				blackKing->getShortCastleRookMoved() = blackKing->getLongCastleRookMoved() = blackKing->getHasMoved() = true;
				break;
			}
			if (!updatePiece(blackKing))
				return false;
		}
		break;
	default:
		break;
	}

	if (!updatedValuesForPoisson)
		pawn->getCurrentRow() = pawn->getCurrentCol() = pawn->getPreviousRow() = INITIAL_VALUE;

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

	updateColorsSquares();
	if ((whiteSquaresBoard[blackKing->getKingRow()][blackKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == BLACK)
		|| (blackSquaresBoard[whiteKing->getKingRow()][whiteKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == WHITE))
	{
		std::cout << "Move is invalid\n";
		board[toRow][toCol] = EMPTY;
		switch (movingPieceType)
		{
		case PAWN:
			board[fromRow][fromCol] = PAWN;
			break;
		case KNIGHT:
			board[fromRow][fromCol] = KNIGHT;
			break;
		case BISHOP:
			board[fromRow][fromCol] = BISHOP;
			break;
		case ROOK:
			board[fromRow][fromCol] = ROOK;
			break;
		case QUEEN:
			board[fromRow][fromCol] = QUEEN;
			break;
		}

		if (colors[toRow][toCol] == WHITE)
		{
			colors[fromRow][fromCol] = WHITE;
			colors[toRow][toCol] = EMPTY;
		}
		else if (colors[toRow][toCol] == BLACK)
		{
			colors[fromRow][fromCol] = BLACK;
			colors[toRow][toCol] = EMPTY;
		}
		updateColorsSquares();
		return false;
	}
	return true;
}

bool Board::updatePiece(std::shared_ptr<Piece> piece)
{
	// Check if move is valid
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