#include "interface.h"
#include <algorithm>

void Interface::hallOfFameInterface(std::vector<Player>& players)
{
	char text[64];
	bool checking = true;
	SDL_FillRect(screen, NULL, black);

	if (players.size())
		std::sort(players.begin(), players.end());

	while (checking)
	{
		if (players.size() == 0)
		{
			DrawRectangle(screen, 4, 200, SCREEN_WIDTH - 8, 75, grey, grey);
			sprintf_s(text, 64, "Player list is empty (type anything to quit)");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 230, text, charset);
		}
		else
		{
			for (size_t i = 0; i < players.size(); i++)
			{
				if (i == 0)
				{
					sprintf_s(text, 64, "Champion: %s", players[i].getName());
					DrawRectangle(screen, 4, 10 + i * 90, SCREEN_WIDTH - 8, 75, grey, gold);
				}
				else if (i == 1)
					DrawRectangle(screen, 4, 10 + i * 90, SCREEN_WIDTH - 8, 75, grey, silver);
				else if (i == 2)
					DrawRectangle(screen, 4, 10 + i * 90, SCREEN_WIDTH - 8, 75, grey, brown);
				else
					DrawRectangle(screen, 4, 10 + i * 90, SCREEN_WIDTH - 8, 75, grey, grey);
				if (i != 0) sprintf_s(text, 64, "%s", players[i].getName());
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 15 + i * 90, text, charset);
				sprintf_s(text, 64, "Wins with white pieces: %d   Wins with black pieces: %d", players[i].getWhiteWins(), players[i].getBlackWins());
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 35 + i * 90, text, charset);
				sprintf_s(text, 64, "Loses with white pieces: %d   Loses with black pieces: %d", players[i].getWhiteLoses(), players[i].getBlackLoses());
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 50 + i * 90, text, charset);

				if (i == 5)
					break;
			}
		}

		SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
		SDL_RenderCopy(renderer, scrtex, NULL, NULL);
		SDL_RenderPresent(renderer);
		checking = hallOfFfameInterfaceEvents();
	}
	SDL_FillRect(screen, NULL, black);
	displayInterface();
}

bool Interface::hallOfFfameInterfaceEvents()
{
	SDL_Event event;
	SDL_WaitEvent(&event);
	switch (event.type) 
	{
	case SDL_MOUSEBUTTONDOWN:
		return false;
	case SDL_KEYDOWN:
		return false;
	case SDL_QUIT:
		return false;
	}
	return true;
}