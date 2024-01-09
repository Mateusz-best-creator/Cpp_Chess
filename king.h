#pragma once

#include "piece.h"

class King : public Piece
{
public:
	King(const char* filename, SDL_Renderer* ren, int x, int y, int bSquare, char c);
	~King();

	void move();

};