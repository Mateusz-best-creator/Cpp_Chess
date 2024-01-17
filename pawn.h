#pragma once

#include "piece.h"
#include <string>
#include <tuple>

class Pawn : public Piece
{
private:
	char color;
	int previousRowPreviousPawn, currentRowPreviousPawn, currentColPreviousPawn;

public:
	Pawn(const char* filename, SDL_Renderer* ren, int bRow, int bColumn, char c);
	~Pawn();

	int& getPreviousRow() { return previousRowPreviousPawn; }
	int& getCurrentRow() { return currentRowPreviousPawn; }
	int& getCurrentCol() { return currentColPreviousPawn; }

	virtual bool move(int toRow, int toCol, char blueRectangles[][8]) override;
	virtual void displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], char blueRectangles[][8], bool forChecks) override;
	void enPassantMove(int fromRow, int fromCol, int toRow, int toCol, char colors[][8], int board[][8], char blueRectangles[][8]);
	void handleEnPassant(char blueRectangles[][8], int board[][8], char colors[][8], int fromRow, int fromCol, int toRow, int toCol, int direction);
};