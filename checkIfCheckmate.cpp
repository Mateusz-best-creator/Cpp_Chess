#include "board.h"

void Board::checkIfCheckmate(int playerIndex)
{
	// Check for checkmate
	if (playerIndex == 1 && whiteKing->checkIfCheckmate(board, colors, whiteSquaresBoard, blackSquaresBoard))
	{
		gameRunning = false;
		std::cout << "Checkmate, black pieces won!\n";
	}
	else if (playerIndex == 2 && blackKing->checkIfCheckmate(board, colors, whiteSquaresBoard, blackSquaresBoard))
	{
		for (int i = 0; i < HEIGHT; i++)
		{
			for (int j = 0; j < WIDTH; j++)
			{
				if (colors[i][j] == BLACK)
				{
					switch (board[i][j])
					{
					case PAWN:
						fromRow = i;
						fromCol = j;
						pawn->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false);
						for (int k = 0; k < HEIGHT; k++)
						{
							for (int h = 0; h < WIDTH; h++)
							{
								if (blueRectanglesBoard[k][h] == 'r')
								{
									toRow = k;
									toCol = h;
									board[fromRow][fromCol] = NONE;
									board[toRow][toCol] = PAWN;
									colors[fromRow][fromCol] = EMPTY;
									colors[toRow][toCol] = BLACK;
									updateColorsSquares();
									if (!((whiteSquaresBoard[blackKing->getKingRow()][blackKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == BLACK)
										|| (blackSquaresBoard[whiteKing->getKingRow()][whiteKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == WHITE)))
									{
										board[fromRow][fromCol] = PAWN;
										board[toRow][toCol] = NONE;
										colors[fromRow][fromCol] = BLACK;
										colors[toRow][toCol] = EMPTY;
										std::cout << "Pawn from " << i << " " << j << " can be moved to " << toRow << " " << toCol << std::endl;
										resetBlueRectanglesBoard();
										blackKing->getCheck() = true;
										return;
									}
									board[fromRow][fromCol] = PAWN;
									board[toRow][toCol] = NONE;
									colors[fromRow][fromCol] = BLACK;
									colors[toRow][toCol] = EMPTY;
									updateColorsSquares();
								}
							}
						}
						break;
					case ROOK:
						fromRow = i;
						fromCol = j;
						rook->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false);
						for (int k = 0; k < HEIGHT; k++)
						{
							for (int h = 0; h < WIDTH; h++)
							{
								if (blueRectanglesBoard[k][h] == 'r')
								{
									toRow = k;
									toCol = h;
									board[fromRow][fromCol] = NONE;
									board[toRow][toCol] = ROOK;
									colors[fromRow][fromCol] = EMPTY;
									colors[toRow][toCol] = BLACK;
									updateColorsSquares();
									if (!((whiteSquaresBoard[blackKing->getKingRow()][blackKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == BLACK)
										|| (blackSquaresBoard[whiteKing->getKingRow()][whiteKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == WHITE)))
									{
										board[fromRow][fromCol] = ROOK;
										board[toRow][toCol] = NONE;
										colors[fromRow][fromCol] = BLACK;
										colors[toRow][toCol] = EMPTY;
										std::cout << "ROOK from " << i << " " << j << " can be moved to " << toRow << " " << toCol << std::endl;
										resetBlueRectanglesBoard();
										blackKing->getCheck() = true;
										return;
									}
									board[fromRow][fromCol] = ROOK;
									board[toRow][toCol] = NONE;
									colors[fromRow][fromCol] = BLACK;
									colors[toRow][toCol] = EMPTY;
									updateColorsSquares();
								}
							}
						}
						break;
					case KNIGHT:
						fromRow = i;
						fromCol = j;
						knight->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false);
						for (int k = 0; k < HEIGHT; k++)
						{
							for (int h = 0; h < WIDTH; h++)
							{
								if (blueRectanglesBoard[k][h] == 'r')
								{
									toRow = k;
									toCol = h;
									board[fromRow][fromCol] = NONE;
									board[toRow][toCol] = KNIGHT;
									colors[fromRow][fromCol] = EMPTY;
									colors[toRow][toCol] = BLACK;
									updateColorsSquares();
									if (!((whiteSquaresBoard[blackKing->getKingRow()][blackKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == BLACK)
										|| (blackSquaresBoard[whiteKing->getKingRow()][whiteKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == WHITE)))
									{
										board[fromRow][fromCol] = KNIGHT;
										board[toRow][toCol] = NONE;
										colors[fromRow][fromCol] = BLACK;
										colors[toRow][toCol] = EMPTY;
										std::cout << "KNIGHT from " << i << " " << j << " can be moved to " << toRow << " " << toCol << std::endl;
										resetBlueRectanglesBoard();
										blackKing->getCheck() = true;
										return;
									}
									board[fromRow][fromCol] = KNIGHT;
									board[toRow][toCol] = NONE;
									colors[fromRow][fromCol] = BLACK;
									colors[toRow][toCol] = EMPTY;
									updateColorsSquares();
								}
							}
						}
						break;
					case BISHOP:
						fromRow = i;
						fromCol = j;
						bishop->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false);
						for (int k = 0; k < HEIGHT; k++)
						{
							for (int h = 0; h < WIDTH; h++)
							{
								if (blueRectanglesBoard[k][h] == 'r')
								{
									toRow = k;
									toCol = h;
									board[fromRow][fromCol] = NONE;
									board[toRow][toCol] = BISHOP;
									colors[fromRow][fromCol] = EMPTY;
									colors[toRow][toCol] = BLACK;
									updateColorsSquares();
									if (!((whiteSquaresBoard[blackKing->getKingRow()][blackKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == BLACK)
										|| (blackSquaresBoard[whiteKing->getKingRow()][whiteKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == WHITE)))
									{
										board[fromRow][fromCol] = BISHOP;
										board[toRow][toCol] = NONE;
										colors[fromRow][fromCol] = BLACK;
										colors[toRow][toCol] = EMPTY;
										std::cout << "BISHOP from " << i << " " << j << " can be moved to " << toRow << " " << toCol << std::endl;
										resetBlueRectanglesBoard();
										blackKing->getCheck() = true;
										return;
									}
									board[fromRow][fromCol] = BISHOP;
									board[toRow][toCol] = NONE;
									colors[fromRow][fromCol] = BLACK;
									colors[toRow][toCol] = EMPTY;
									updateColorsSquares();
								}
							}
						}
						break;
					case QUEEN:
						fromRow = i;
						fromCol = j;
						queen->displayBlueRectangles(fromRow, fromCol, board, colors, blueRectanglesBoard, false);
						for (int k = 0; k < HEIGHT; k++)
						{
							for (int h = 0; h < WIDTH; h++)
							{
								if (blueRectanglesBoard[k][h] == 'r')
								{
									toRow = k;
									toCol = h;
									board[fromRow][fromCol] = NONE;
									board[toRow][toCol] = QUEEN;
									colors[fromRow][fromCol] = EMPTY;
									colors[toRow][toCol] = BLACK;
									updateColorsSquares();
									if (!((whiteSquaresBoard[blackKing->getKingRow()][blackKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == BLACK)
										|| (blackSquaresBoard[whiteKing->getKingRow()][whiteKing->getKingColumn()] != EMPTY && colors[toRow][toCol] == WHITE)))
									{
										board[fromRow][fromCol] = QUEEN;
										board[toRow][toCol] = NONE;
										colors[fromRow][fromCol] = BLACK;
										colors[toRow][toCol] = EMPTY;
										std::cout << "QUEEN from " << i << " " << j << " can be moved to " << toRow << " " << toCol << std::endl;
										resetBlueRectanglesBoard();
										blackKing->getCheck() = true;
										return;
									}
									board[fromRow][fromCol] = QUEEN;
									board[toRow][toCol] = NONE;
									colors[fromRow][fromCol] = BLACK;
									colors[toRow][toCol] = EMPTY;
									updateColorsSquares();
								}
							}
						}
						break;
					}
				}
				resetBlueRectanglesBoard();
			}
		}
		gameRunning = false;
		std::cout << "Checkmate, white pieces won!\n";
	}
}