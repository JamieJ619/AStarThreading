#pragma once
#include <SDL.h>

class Tile
{
public:
	Tile(int x, int y, int width, int height, int id);
	~Tile();

	void render(SDL_Renderer * renderer);
	void setColor(SDL_Renderer * renderer);
private:
	SDL_Rect m_tileRect;
};

