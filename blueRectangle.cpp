#include "blueRectangle.h"
#include "textureManager.h"

BlueRectangle::BlueRectangle(const char* filename, SDL_Renderer* ren, int bRow, int bColumn)
{
	xPosition = yPosition = 0;
	renderer = ren;
	objectTexture = TextureManager::LoadTexture(filename, ren);

	boardRow = bRow;
	boardColumn = bColumn;
}

BlueRectangle::~BlueRectangle() {}

void BlueRectangle::calculateXY()
{
	xPosition = (boardColumn - 1) * (PIECES_X_DISTANCE - 1) + 44;
	yPosition = 600 - 33 - boardRow * PIECES_Y_DISTANCE;
}

void BlueRectangle::update()
{
	calculateXY();
	sourceRect.h = 69;
	sourceRect.w = 90;
	sourceRect.x = 0;
	sourceRect.y = 0;

	destinationRect.x = xPosition;
	destinationRect.y = yPosition;
	destinationRect.w = sourceRect.w; 
	destinationRect.h = sourceRect.h;
}

void BlueRectangle::render()
{
	SDL_RenderCopy(renderer, objectTexture, &sourceRect, &destinationRect);
}