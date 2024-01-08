#include "piece.h"
#include "textureManager.h"

Piece::Piece(const char* filename, SDL_Renderer* ren, int x, int y)
{
	renderer = ren;
	objectTexture = TextureManager::LoadTexture(filename, ren);

	xPosition = x;
	yPosition = y;
}

void Piece::update()
{
	sourceRect.h = 64;
	sourceRect.w = 64;
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