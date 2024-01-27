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

	// Getters and setters
	char* getName() { return name; }
	const char* getName() const { return name; }
	Colors& getPlayingColor() { return currentPlayingColor; }
	Colors getPlayingColor() const { return currentPlayingColor; }
	int& getWhiteWins() { return whiteWins; }
	int& getBlackWins() { return blackWins; }
	int& getWhiteLoses() { return whiteLoses; }
	int& getBlackLoses() { return blackLoses; }

	bool operator<(const Player& p);
};