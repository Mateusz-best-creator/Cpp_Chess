#pragma once

#include "board.h"

class Player
{
private:
	int whiteWins, blackWins, whiteLoses, blackLoses;
	char name[30];
	Colors currentPlayingColor;

public:
	Player() = default;
	Player(const char*, Colors);

	char* getName() { return name; }
	Colors& getPlayingColor() { return currentPlayingColor; }
	Colors getPlayingColor() const { return currentPlayingColor; }
};