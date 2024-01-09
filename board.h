#pragma once

#include "piece.h"

const int HEIGHT = 8, WIDTH = 8, INITIAL_PIECES_NUMBER = 32;
const int PIECES_X_DISTANCE = 90, PIECES_Y_DISTANCE = 67;

class Board
{
private:
	enum colors : int { WHITE, BLACK, EMPTY };
	enum pieces_types : int { NONE = 0, ROOK, KNIGHT, BISHOP, KING, QUEEN, PAWN = 6 };
	int board[HEIGHT][WIDTH] =
	{
		{1, 2, 3, 4, 5, 3, 2, 1},
		{6, 6, 6, 6, 6, 6, 6, 6},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{6, 6, 6, 6, 6, 6, 6, 6},
		{1, 2, 3, 4, 5, 3, 2, 1}
	};
	char colors[HEIGHT][WIDTH] =
	{
		{'w', 'w', 'w', 'w', 'w', 'w' , 'w', 'w'},
		{'w', 'w', 'w', 'w', 'w', 'w' , 'w', 'w'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'b', 'b', 'b', 'b', 'b', 'b' , 'b', 'b'},
		{'b', 'b', 'b', 'b', 'b', 'b' , 'b', 'b'},
	};

	SDL_Texture* boardTexture;
	SDL_Renderer* renderer;

	Piece* pieces[INITIAL_PIECES_NUMBER];

public:
	Board(const char* filename, SDL_Renderer* ren);
	~Board();

	void render();
	void update();
};