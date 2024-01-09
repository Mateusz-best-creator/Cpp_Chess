#pragma once

#include "piece.h"

class Bishop : public Piece
{
public:
	Bishop(const char* filename, SDL_Renderer* ren, int x, int y, int bSquare, char c);
	~Bishop();

	void move();

};