#include "player.h"
#include <cstring>

Player::Player(const char* n, Colors c)
{
	currentPlayingColor = c;
	whiteWins = blackWins = whiteLoses = blackLoses = 0;
	int i;
	for (i = 0; i < strlen(n); i++)
		name[i] = n[i];
	name[i] = '\0';
}

bool Player::operator<(const Player& p)
{
	if (blackWins + whiteWins > p.blackWins + p.whiteWins)
		return false;
	else if (blackWins + whiteWins == p.blackWins + p.whiteWins && blackLoses + whiteLoses < p.blackLoses + p.whiteLoses)
	{
		return false;
	}
	else if (blackWins + whiteWins == p.blackWins + p.whiteWins && whiteLoses + blackLoses == p.whiteLoses + p.blackLoses)
		return false;

	return true;
}