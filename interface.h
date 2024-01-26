#pragma once

#include "game.h"
#include "icon.h"
#include "player.h"
#include <vector>

const int NUMBER_INTERFACE_ICONS = 3, ICON_Y = 400, NAME_MAX_LENGTH = 30;

class Interface
{
private:
	// Text format
	enum class Format { Big, Medium, Small };

	SDL_Event event;
	// Load screen and BMP icons
	SDL_Surface* screen, * charset, * trophyIcon = nullptr, * authenticateIcon = nullptr, * playIcon = nullptr;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;
	int quit, rc;

	bool display;
	char text[256];
	int black, green, red, blue, white, grey;

	std::vector<Player> players;
	char whitePlayerName[NAME_MAX_LENGTH] = { "Unknown" };
	char blackPlayerName[NAME_MAX_LENGTH] = { "Unknown" };

public:
	Interface();
	~Interface();

	void showInterface();
	void displayInterface();
	int displayAuthenticationInterface(std::vector<Player>&);
	bool handleAuthenticationInterfaceEvents(char* name, int& index, bool choosingColor = false);

	void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset, Format format = Format::Small);
	void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
	void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
	void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);

	bool getDisplay() { return display; };
};