#pragma once

#include "piece.h"

class Queen : public Piece
{
public:
	Queen(const char* filename, SDL_Renderer* ren, int x, int y, int bSquare, char c);
	~Queen();

	void move();

};