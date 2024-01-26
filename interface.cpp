#include "interface.h"
#include <vector>

// Global variable for storing players
std::vector<Player> players;
char whitePlayerName[NAME_MAX_LENGTH] = { "Unknown" };
char blackPlayerName[NAME_MAX_LENGTH] = { "Unknown" };

Interface::Interface()
	: display(false)
{
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,  &window, &renderer);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	if (screen == nullptr) 
	{
		std::cerr << "Error creating surface: " << SDL_GetError() << std::endl;
	}

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./ChessPieces/cs8x8.bmp");
	SDL_SetColorKey(charset, true, 0x000000);

	black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	blue = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	white = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
	grey = SDL_MapRGB(screen->format, 0x24, 0x24, 0x24);
	quit = 0;
	text[0] = '\0';

	trophyIcon = SDL_LoadBMP("./ChessPieces/golden_cup.bmp");
	authenticateIcon = SDL_LoadBMP("./ChessPieces/golden_cup.bmp");
	playIcon = SDL_LoadBMP("./ChessPieces/golden_cup.bmp");
}

Interface::~Interface()
{
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Interface::displayInterface()
{
	DrawSurface(screen, playIcon, 150, ICON_Y);
	DrawSurface(screen, authenticateIcon, 405, ICON_Y);
	DrawSurface(screen, trophyIcon, SCREEN_WIDTH - 150, ICON_Y);

	// display all the rectangles and text
	DrawRectangle(screen, 4, 20, SCREEN_WIDTH - 8, 75, white, grey);
	sprintf_s(text, 256, "C++ creafted chess game made by Mateusz Wieczorek");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 30, text, charset, Format::Big);
	sprintf_s(text, 256, "Click appropriate rectangle to choose what you want to do.");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 50, text, charset);
	sprintf_s(text, 256, "1 - play chess   2 - authenticate yourself in database   3 - check HallOfFame");
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 70, text, charset);

	DrawRectangle(screen, 4, SCREEN_HEIGHT - 55, SCREEN_WIDTH - 8, 55, white, grey);
	sprintf_s(text, 256, "White player is currently logged as: %s", whitePlayerName);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 560, text, charset, Format::Medium);
	sprintf_s(text, 256, "Black player is currently logged as: %s", blackPlayerName);
	DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 580, text, charset, Format::Medium);

	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);

	
}

void Interface::showInterface()
{
	std::cout << "Quit value = " << quit << std::endl;
	displayInterface();
	while (!quit) 
	{
		
		while (SDL_PollEvent(&event)) 
		{
			switch (event.type) 
			{
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = 1;
					exit(EXIT_SUCCESS);
				}
				else if (event.key.keysym.sym == SDLK_1)
				{
					display = true;
					quit = 1;
				}
				else if (event.key.keysym.sym == SDLK_2)
				{
					authenticationInterface();
				}
				else if (event.key.keysym.sym == SDLK_3)
				{

				}
				break;
			case SDL_QUIT:
				exit(EXIT_SUCCESS);
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					int xValue = event.button.x;
					int yValue = event.button.y;

					if (xValue >= 70 && xValue <= 229 && yValue >= 312 && yValue <= 478)
					{
						display = true;
						quit = 1;
					}
					else if (xValue >= 255 + 70 && xValue <= 255 + 229 && yValue >= 312 && yValue <= 478)
						authenticationInterface();
					else if (xValue >= 255 + 255 + 70 && xValue <= 255 + 255 + 229 && yValue >= 312 && yValue <= 478)
					{
						std::cout << "Getting event for HallOfFame\n";
					}
				}
			}
		};
	};
}

void Interface::authenticationInterface()
{
	int index = displayAuthenticationInterface(players);

	if (index != players.size() - 1 || (players.size() == 1 && index == 0))
	{
		strcpy_s(whitePlayerName, NAME_MAX_LENGTH, "Unknown");
		strcpy_s(blackPlayerName, NAME_MAX_LENGTH, "Unknown");
	}

	if (players[index].getPlayingColor() == WHITE)
		strcpy_s(whitePlayerName, NAME_MAX_LENGTH, players[index].getName());
	else
		strcpy_s(blackPlayerName, NAME_MAX_LENGTH, players[index].getName());

	displayInterface();
}

/*
draw a text txt on surface screen, starting from the point (x, y)
charset is a 128x128 bitmap containing character images
*/
void Interface::DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset, Format format) 
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;

	int charWidth;  // Desired character width
	int charHeight;  // Desired character height
	switch (format)
	{
	case Format::Big:
		charHeight = charWidth = 40;
		break;
	case Format::Medium:
		charHeight = charWidth = 20;
		break;
	case Format::Small:
		charHeight = charWidth = 8;
		break;
	default:
		charHeight = charWidth = 8;
		break;
	}

	d.w = charWidth;
	d.h = charHeight;

	while (*text) 
	{
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		// Letter spacing
		x += 8;
		text++;
	};
};

// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void Interface::DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y)
{
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

// draw a single pixel
void Interface::DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void Interface::DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color)
{
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

// draw a rectangle of size l by k
void Interface::DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor)
{
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};