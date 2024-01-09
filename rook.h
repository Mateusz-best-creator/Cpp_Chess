#pragma once

#include "piece.h"

class Rook : public Piece
{
public:
	Rook(const char* filename, SDL_Renderer* ren, int x, int y, int bSquare, char c);
	~Rook();

	void move();

};