#pragma once

#include "piece.h"

const int HEIGHT = 8, WIDTH = 8, INITIAL_PIECEC_NUMBER = 32;

class Board
{
private:
	enum colors : int { WHITE, BLACK, EMPTY };
	enum pieces_types : int { ROOK = 0, KNIGHT, BISHOP, QUENN, KING, PAWN = 5, NONE };
	int board[HEIGHT][WIDTH];
	int colors[HEIGHT][WIDTH];

	SDL_Texture* boardTexture;
	SDL_Renderer* renderer;

	Piece* pieces[INITIAL_PIECEC_NUMBER];

public:
	Board(const char* filename, SDL_Renderer* ren);
	~Board();

	void render();
};