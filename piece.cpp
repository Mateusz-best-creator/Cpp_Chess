#include "piece.h"
#include "textureManager.h"

Piece::Piece(const char* filename, SDL_Renderer* ren, int x, int y, int bSquare, char c)
{
	renderer = ren;
	objectTexture = TextureManager::LoadTexture(filename, ren);

	xPosition = x;
	yPosition = y;
	boardSquare = bSquare;
	color = c;
}

Piece::~Piece() {}

void Piece::update()
{
	sourceRect.h = PIECE_HEIGHT;
	sourceRect.w = PIECE_WIDTH;
	sourceRect.x = 0;
	sourceRect.y = 0;

	destinationRect.x = xPosition; 
	destinationRect.y = yPosition;
	destinationRect.w = sourceRect.w;
	destinationRect.h = sourceRect.h;
}

void Piece::render()
{
	SDL_RenderCopy(renderer, objectTexture, &sourceRect, &destinationRect);
}