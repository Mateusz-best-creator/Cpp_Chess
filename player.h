#pragma once

#include "board.h"

class Player
{
private:
	int whiteWins, blackWins, whiteLoses, blackLoses;
	char name[30];
	Colors playingColor;

public:
	Player() = default;
	Player(const char* n);

	char* getName() { return name; }
	Colors& getPlayingColor() { return playingColor; }
	Colors getPlayingColor() const { return playingColor; }
};