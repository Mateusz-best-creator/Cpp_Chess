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
	xPosition = boardColumn * PIECES_X_DISTANCE - 38;
	yPosition = 35 - 67 + boardRow * PIECES_Y_DISTANCE;
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

int Piece::absoluteValue(int a, int b)
{
	if (a - b < 0)
		return b - a;
	return a - b;
}