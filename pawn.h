#pragma once

#include "piece.h"

class Pawn : public Piece
{
private:
	int boardSquare;
	char color;

	const char pawn_filename_white[30] = "ChessPieces/Chess_plt60.png";
	const char pawn_filename_black[30] = "ChessPieces/Chess_pdt60.png";

public:
	Pawn(const char* filename, SDL_Renderer* ren, int x, int y, int bRow, int bColumn, char c);
	~Pawn();

	void move();

};