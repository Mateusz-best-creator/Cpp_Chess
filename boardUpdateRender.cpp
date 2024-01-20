#include "board.h"

bool Board::update()
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
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (board[i][j] == NONE)
				continue;
			addPieces(i, j, 8 - i);
		}
	}
	int counter = 0;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (blueRectanglesBoard[i][j] != EMPTY)
				rectangles[counter]->update();
			counter++;
		}
	}

	for (int i = 0; i < pieces.size(); i++)
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
	return gameRunning;
}

void Board::render()
{
	// Render the board
	SDL_RenderCopy(renderer, boardTexture, &sourceRect, &destinationRect);

	// Render all blue rectangles
	int counter = 0;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
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
	for (int i = 0; i < pieces.size(); i++)
		pieces[i]->render();
}