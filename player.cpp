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

/*
Comparison for sorting in descending order
*/
bool Player::operator<(const Player& p)
{
    if (blackWins + whiteWins > p.blackWins + p.whiteWins)
        return true;
    else if (blackWins + whiteWins == p.blackWins + p.whiteWins && blackLoses + whiteLoses > p.blackLoses + p.whiteLoses)
        return true;
    else if (blackWins + whiteWins == p.blackWins + p.whiteWins && whiteLoses + blackLoses == p.whiteLoses + p.blackLoses)
        return false;

    return false;
}