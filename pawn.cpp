#include "pawn.h"
#include "textureManager.h"

Pawn::Pawn(const char* filename, SDL_Renderer* ren, int x, int y, int bRow, int bColumn, char c)
	: Piece(filename, ren, x, y, bRow, bColumn, c)
{}

Pawn::~Pawn() {}

void Pawn::move()
{

}
