#include "textureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename, SDL_Renderer* ren)
{
	SDL_Surface* surface = IMG_Load(filename);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, surface);
	SDL_FreeSurface(surface);
	return texture;
}