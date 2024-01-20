#pragma once

#include "piece.h"
#include <iostream>

class King : public Piece
{
private:
	int kingRow, kingColumn;
	char kingColor;
	bool check, hasMoved, shortCastleRookMoved, longCastleRookMoved;

public:
	King(const char* filename, SDL_Renderer* ren, int bRow, int bCol, char c);
	~King();

	// Getters
	bool getCheck() const { return check; }
	bool& getCheck() { return check; }
	bool getHasMoved() const { return hasMoved; }
	bool& getHasMoved() { return hasMoved; }
	bool getShortCastleRookMoved() const { return shortCastleRookMoved; }
	bool getLongCastleRookMoved() const { return longCastleRookMoved; }
	bool& getShortCastleRookMoved() { return shortCastleRookMoved; }
	bool& getLongCastleRookMoved() { return longCastleRookMoved; }
	int getKingRow() const { return kingRow; }
	int getKingColumn() const { return kingColumn; }
	int& getKingRow() { return kingRow; }
	int& getKingColumn() { return kingColumn; }
	char getKingcolor() const { return kingColor; }

	virtual bool move(int toRow, int toCol, char blueRectangles[][8]) override;
	virtual void displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8],
		char blueRectangles[][8], bool forChecks) override {}
	virtual void displayBlueRectangles(int fromRow, int fromCol, int board[][8], char colors[][8], 
		char blueRectangles[][8], bool forChecks, char whiteColorsSquares[][8], char blackColorsSquares[][8]);
	void updateRectangles(char color, int fromRow, int fromCol, int board[][8], char colors[][8], 
		char blueRectangles[][8], bool forChecks, char colorsSquares[][8]);
	void assignArray(char boardTocheck[][8], char colorsSquares[][8]);

	bool checkIfMoveValid(int toRow, int toColumn, char colorsSquares[][8]);
	void calculateDestination(int fromRow, int fromCol, int direction[], int& toRow, int& toCol);
	bool isValidSquare(int row, int col);
	bool isValidMove(char color, int toRow, int toCol, char colors[][8], bool forChecks, char colorsSquares[][8]);

	// Functions for checking if there is a check or checkmate
	bool checkIfCheck(char boardToCheck[][8]);
	bool checkIfKingHasSquare(int board[][8], char colors[][8], char whiteColorsSquares[][8], char blackColorsSquares[][8]);
	bool canMoveTo(char colors[][8], char occupiedSquares[][8], int row, int col);
};