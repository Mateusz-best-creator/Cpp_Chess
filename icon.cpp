#include "icon.h"
#include "textureManager.h"

Icon::Icon(const char* filename, SDL_Renderer* ren)
	: renderer(ren), destinationX(200), destinationY(200)
{
	objectTexture = TextureManager::LoadTexture(filename, ren);
}

Icon::~Icon() {}

void Icon::update()
{
	sourceRect.h = ICON_HEIGHT;
	sourceRect.w = ICON_WIDTH;
	sourceRect.x = 0;
	sourceRect.y = 0;

	destinationRect.x = 50;
	destinationRect.y = 250;
	destinationRect.w = sourceRect.w;
	destinationRect.h = sourceRect.h;
}

void Icon::render()
{
	SDL_RenderCopy(renderer, objectTexture, &sourceRect, &destinationRect);
}