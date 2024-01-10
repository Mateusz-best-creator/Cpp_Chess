#include "interface.h"
#include <iostream>
#include <string>

Interface::Interface()
{
	text[0] = '\0';

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	charset = SDL_LoadBMP("./cs8x8.bmp");

	// Initialize all of the colors
	colors[0] = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	colors[1] = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	colors[2] = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	colors[3] = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
}

Interface::~Interface() 
{
	// freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
}

void Interface::drawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) 
{
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

void Interface::printInterface()
{
	SDL_FillRect(screen, NULL, colors[0]);

	drawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, colors[2], colors[3]);
	char templateInfo[100];
	sprintf_s(templateInfo, sizeof(templateInfo), "Szablon drugiego zadania");
	drawString(screen, screen->w / 2 - strlen(templateInfo) * 8 / 2, 10, templateInfo, charset);
	char keyInstructions[100];
	sprintf_s(keyInstructions, sizeof(keyInstructions), "Esc - wyjscie, \030 - przyspieszenie, \031 - zwolnienie");
	drawString(screen, screen->w / 2 - strlen(keyInstructions) * 8 / 2, 26, keyInstructions, charset);
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);

}

void Interface::drawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor)
{
	int i;
	drawLine(screen, x, y, k, 0, 1, outlineColor);
	drawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	drawLine(screen, x, y, l, 1, 0, outlineColor);
	drawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		drawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
}

void Interface::drawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color)
{
	for (int i = 0; i < l; i++)
	{
		drawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

void Interface::drawPixel(SDL_Surface* surface, int x, int y, Uint32 color)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

void Interface::drawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset) 
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};