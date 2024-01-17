#include "board.h"

// Helper function
void Board::resetBlueRectanglesBoard()
{
	// Reset blue rectangles
	for (size_t i = 0; i < HEIGHT; i++)
		for (size_t j = 0; j < WIDTH; j++)
			blueRectanglesBoard[i][j] = EMPTY;
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