#pragma once

#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "blueRectangle.h"

#include <vector>
#include <memory>
#include <iostream>

const int HEIGHT = 8, WIDTH = 8, INITIAL_PIECES_NUMBER = 32;
const int PIECES_X_DISTANCE = 90, PIECES_Y_DISTANCE = 67;
const int X_OFFSET = 42, Y_OFFSET = 29;

class Board
{
private:
	enum colors : int { WHITE, BLACK, EMPTY };
	enum pieces_types : int { NONE = 0, ROOK, KNIGHT, BISHOP, KING, QUEEN, PAWN = 6 };
	int board[HEIGHT][WIDTH] =
	{
		{1, 2, 3, 5, 4, 3, 2, 1},
		{6, 6, 6, 6, 6, 6, 6, 6},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 6, 6, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 6, 6},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{6, 6, 6, 6, 6, 6, 6, 6},
		{1, 2, 3, 5, 4, 3, 2, 1}
	};
	char colors[HEIGHT][WIDTH] =
	{
		{'w', 'w', 'w', 'w', 'w', 'w' , 'w', 'w'},
		{'w', 'w', 'w', 'w', 'w', 'w' , 'w', 'w'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'b', 'w', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'w', 'w'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'b', 'b', 'b', 'b', 'b', 'b' , 'b', 'b'},
		{'b', 'b', 'b', 'b', 'b', 'b' , 'b', 'b'},
	};
	char blueRectanglesBoard[HEIGHT][WIDTH] =
	{
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'b', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'}
	};

	SDL_Texture* boardTexture, * blueRectangleTexture;
	SDL_Renderer* renderer;
	SDL_Rect sourceRect, destinationRect;

	std::vector<std::unique_ptr<BlueRectangle>> rectangles;
	std::vector<std::unique_ptr<Piece>> pieces;
	

public:
	Board(const char* filename, SDL_Renderer* ren);
	~Board();

	void render();
	void update();
	void updatePiece(int initRow, int initColumn, int destRow, int destColumn) {} // Not implemented yet
	void choosingPiece(int row, int column);
};