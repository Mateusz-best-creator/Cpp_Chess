#pragma once

#include "SDL.h"
const int SCREEN_HEIGHT = 600, SCREEN_WIDTH = 1200;

class Interface
{
private:
	int colors[4];
	char text[100];
	SDL_Renderer* renderer;
	SDL_Surface* screen, * charset;
	SDL_Texture* scrtex;

public:
	Interface();
	~Interface();

	void drawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
	void printInterface();
	void drawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);
	void drawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	void drawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
	void drawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);
};