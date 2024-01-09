#pragma once

#include "piece.h"

class Pawn : public Piece
{
private:
	int xPosition, yPosition;


public:
	Pawn(const char* filename, int x, int y);
	~Pawn();

	void move();
};