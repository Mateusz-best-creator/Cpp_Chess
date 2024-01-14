#pragma once

#include "piece.h"
#include <string>

class Pawn : public Piece
{
private:
	int boardSquare;
	char color;

public:
	Pawn(const char* filename, SDL_Renderer* ren, int bRow, int bColumn, char c);
	~Pawn();

	virtual bool move(int fromRow, int fromCol, int toRow, int toCol, int board[][8], char colors[][8], char blueRectangles[][8]) override;
	virtual void displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8]) override;
};