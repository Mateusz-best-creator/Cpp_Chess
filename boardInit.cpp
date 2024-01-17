#include "board.h"
#include "textureManager.h"

Board::Board(const char* filename, SDL_Renderer* ren)
{
	renderer = ren;
	boardTexture = TextureManager::LoadTexture(filename, renderer);
	movingPieceType = NONE;
	redRectangle = std::make_unique<BlueRectangle>("ChessPieces/red.png", renderer, 1, 1);

	int boardR = 0;
	pieces.clear();
	rectangles.clear();

	for (int i = 0; i < HEIGHT; i++)
	{
		// Get current row on board
		boardR = 8 - i;

		for (int j = 0; j < WIDTH; j++)
		{
			rectangles.push_back(std::make_unique<BlueRectangle>("ChessPieces/blue.png", renderer, i + 1, j + 1));

			if (colors[i][j] == EMPTY)
				continue;
			addPieces(i, j, boardR);
		}
	}
	fromRow = fromCol = toRow = toCol = -1;
	// Create seperate instance of each pawn for simplicity
	pawn = std::make_shared<Pawn>("ChessPieces/Chess_plt60.png", renderer, 1, 1, WHITE);
	rook = std::make_shared<Rook>("ChessPieces/Chess_rlt60.png", renderer, 1, 1, WHITE);
	knight = std::make_shared<Knight>("ChessPieces/Chess_ndt60.png", renderer, 1, 1, WHITE);
	bishop = std::make_shared<Bishop>("ChessPieces/Chess_ndt60.png", renderer, 1, 1, WHITE);
	queen = std::make_shared<Queen>("ChessPieces/Chess_ndt60.png", renderer, 1, 1, WHITE);
	whiteKing = std::make_shared<King>("ChessPieces/Chess_ndt60.png", renderer, 1, 5, WHITE);
	blackKing = std::make_shared<King>("ChessPieces/Chess_ndt60.png", renderer, 8, 5, BLACK);
}

Board::~Board() 
{
	rectangles.clear();
	pieces.clear();
}

void Board::addPieces(int i, int j, int boardR)
{
	switch (board[i][j])
	{
	case PAWN:

		if (colors[i][j] == WHITE)
			pieces.push_back(std::make_shared<Pawn>
				("ChessPieces/Chess_plt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<Pawn>
				("ChessPieces/Chess_pdt60.png", renderer, boardR, j + 1, BLACK));
		break;
	case ROOK:
		if (colors[i][j] == WHITE)
			pieces.push_back(std::make_shared<Rook>
				("ChessPieces/Chess_rlt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<Rook>
				("ChessPieces/Chess_rdt60.png", renderer, boardR, j + 1, BLACK));
		break;
	case KNIGHT:
		if (colors[i][j] == WHITE)
			pieces.push_back(std::make_shared<Knight>
				("ChessPieces/Chess_nlt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<Knight>
				("ChessPieces/Chess_ndt60.png", renderer, boardR, j + 1, BLACK));
		break;
	case BISHOP:
		if (colors[i][j] == WHITE)
			pieces.push_back(std::make_shared<Bishop>
				("ChessPieces/Chess_blt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<Bishop>
				("ChessPieces/Chess_bdt60.png", renderer, boardR, j + 1, BLACK));
		break;
	case QUEEN:
		if (colors[i][j] == WHITE)
			pieces.push_back(std::make_shared<Queen>
				("ChessPieces/Chess_qlt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<Queen>
				("ChessPieces/Chess_qdt60.png", renderer, boardR, j + 1, BLACK));
		break;
	case KING:
		if (colors[i][j] == 'w')
			pieces.push_back(std::make_shared<King>
				("ChessPieces/Chess_klt60.png", renderer, boardR, j + 1, WHITE));
		else if (colors[i][j] == BLACK)
			pieces.push_back(std::make_shared<King>
				("ChessPieces/Chess_kdt60.png", renderer, boardR, j + 1, BLACK));
		break;
	}
}