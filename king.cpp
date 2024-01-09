#include "king.h"

King::King(const char* filename, SDL_Renderer* ren, int x, int y, int bSquare, char c)
	: Piece(filename, ren, x, y, bSquare, c)
{}

King::~King() {}

void King::move()
{

}