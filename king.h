#pragma once

#include "piece.h"

class King : public Piece
{
private:
	int kingRow, kingColumn;
	bool check;

public:
	King(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c);
	~King();

	bool getCheck() { return check; }
	int getKingRow() { return kingRow; }
	int getKingColumn() { return kingColumn; }

	virtual bool move(int toRow, int toCol, char blueRectangles[][8]) override;
	virtual void displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8],
		char blueRectangles[][8], bool forChecks) override {}
	virtual void displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], 
		char blueRectangles[][8], bool forChecks, char whiteColorsSquares[][8], char blackColorsSquares[][8]);
	void updateRectangles(char color, int fromRow, int fromCol, int board[][8], char colors[][8], 
		char blueRectangles[][8], bool forChecks, char colorsSquares[][8]);

	bool checkIfMoveValid(int toRow, int toColumn, char colorsSquares[][8]);
	void calculateDestination(int fromRow, int fromCol, int direction[], int& toRow, int& toCol);
	bool isValidSquare(int row, int col);
	bool isValidMove(char color, int toRow, int toCol, char colors[][8], bool forChecks, char colorsSquares[][8]);
};