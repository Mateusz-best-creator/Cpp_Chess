#pragma once

#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "blueRectangle.h"
#include "errorsObjects.h"

#include <vector>
#include <memory>
#include <iostream>
#include <string>

const int HEIGHT = 8, WIDTH = 8, INITIAL_PIECES_NUMBER = 32;
const int PIECES_X_DISTANCE = 90, PIECES_Y_DISTANCE = 67;
const int X_OFFSET = 42, Y_OFFSET = 29;

enum Colors : char { WHITE = 'w', BLACK = 'b', EMPTY = 'e', BLUE_RECTANGLE = 'r' };
enum PieceTypes : int { NONE = 0, ROOK, KNIGHT, BISHOP, KING, QUEEN, PAWN = 6 };

class Board
{

private:
	int board[HEIGHT][WIDTH] =
	{
		{1, 2, 3, 5, 4, 3, 2, 1},
		{6, 6, 6, 6, 6, 6, 6, 6},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{6, 6, 6, 6, 6, 6, 6, 6},
		{1, 2, 3, 5, 4, 3, 2, 1}
	};
	char colors[HEIGHT][WIDTH] =
	{
		{'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
		{'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
		{'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'},
		{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'},
		{'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'}
	};
	char blueRectanglesBoard[HEIGHT][WIDTH] =
	{
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'}
	};
	// Board which indicate which squares "can be" under control for each color (useful for checks)
	char whiteSquaresBoard[HEIGHT][WIDTH] =
	{
		{'o', 'o', 'o', 'o', 'o', 'o' , 'o', 'o'},
		{'o', 'o', 'o', 'o', 'o', 'o' , 'o', 'o'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'}
	};
	char blackSquaresBoard[HEIGHT][WIDTH] =
	{
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'e', 'e', 'e', 'e', 'e', 'e' , 'e', 'e'},
		{'o', 'o', 'o', 'o', 'o', 'o' , 'o', 'o'},
		{'o', 'o', 'o', 'o', 'o', 'o' , 'o', 'o'}
	};

	SDL_Texture* boardTexture, * blueRectangleTexture;
	SDL_Renderer* renderer;
	SDL_Rect sourceRect, destinationRect;

	std::vector<std::unique_ptr<BlueRectangle>> rectangles;
	std::vector<std::unique_ptr<Piece>> pieces; // Polymorphism
	std::shared_ptr<Pawn> pawn;
	std::shared_ptr<Rook> rook;
	std::shared_ptr<Knight> knight;
	std::shared_ptr<Bishop> bishop;
	std::shared_ptr<Queen> queen;
	std::shared_ptr<King> king;

	int fromRow, fromCol;
	int toRow, toCol;
	int movingPieceType;
	enum { INITIAL_VALUE = -1 };
	

public:
	Board(const char* filename, SDL_Renderer* ren);
	~Board();

	void render();
	void update();
	void addPieces(int i, int j, int boardR);
	void movingPiece(int row, int column, int& playerIndex);

	// Functions for updating pieces
	bool updatePieces();
	bool updatePiece(std::shared_ptr<Piece> piece);

	// Functions for updating occupied squares
	void updateColorsSquares(char boardToUpdate[][8]);
};