#include "piece.h"
#include "textureManager.h"

Piece::Piece(const char* filename, SDL_Renderer* ren, int bRow, int bColumn, char c)
{
	renderer = ren;
	objectTexture = TextureManager::LoadTexture(filename, ren);

	boardRow = bRow;
	boardColumn = bColumn;
	color = c;
}

Piece::~Piece() {}

void Piece::calculateXY()
{
	xPosition = 310 + 53 + boardColumn * PIECES_X_DISTANCE;
	yPosition = 536 - (35 - 67 + boardRow * PIECES_Y_DISTANCE);
}

void Piece::update()
{
	calculateXY();

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