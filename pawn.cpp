
/*
Pawn::Pawn(const char* filename, SDL_Renderer* ren, int x, int y, int bSquare, char c)
{
	boardSquare = bSquare;
	color = c;
	xPosition = x;
	yPosition = y;

	renderer = ren;
	objectTexture = TextureManager::LoadTexture(filename, ren);
}

Pawn::~Pawn() {}

void Pawn::update()
{
	sourceRect.h = PIECE_HEIGHT;
	sourceRect.w = PIECE_WIDTH;
	sourceRect.x = 0;
	sourceRect.y = 0;

	destinationRect.x = xPosition;
	destinationRect.y = yPosition;
	destinationRect.w = sourceRect.w;
	destinationRect.h = sourceRect.h;
}

void Pawn::render()
{
	SDL_RenderCopy(renderer, objectTexture, &sourceRect, &destinationRect);
}

void Pawn::move()
{

}
*/