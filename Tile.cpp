#include "Tile.h"
#include <cstdlib>


Tile::Tile(int p_x, int p_y, int p_width, int p_height, int p_id)
{
	m_tileRect = { p_x, p_y, p_width, p_height};
}


Tile::~Tile()
{

}

void Tile::render(SDL_Renderer * p_renderer)
{
	SDL_RenderFillRect(p_renderer, &m_tileRect);

	setColor(p_renderer);
}

void Tile::setColor(SDL_Renderer * p_renderer)
{
	SDL_SetRenderDrawColor(p_renderer, rand() % 255, rand() % 255, rand() % 255, 255);
}
