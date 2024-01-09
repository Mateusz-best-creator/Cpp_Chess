#pragma once

#include "piece.h"

class Knight : public Piece
{
public:
	Knight(const char* filename, SDL_Renderer* ren, int x, int y, int bSquare, char c);
	~Knight();

	void move();

};