#include "Tile.h"
#include <cstdlib>


Tile::Tile(int p_x, int p_y, int p_width, int p_height, int p_id)
{
	m_tileRect = { p_x, p_y, p_width, p_height};
}


Tile::~Tile()
{

}

void Tile::render(SDL_Renderer * p_renderer, SDL_Point p_cameraPosition)
{
	SDL_Rect temp{ m_tileRect.x - p_cameraPosition.x, m_tileRect.y - p_cameraPosition.y, m_tileRect.w, m_tileRect.h };
	SDL_RenderFillRect(p_renderer, &temp);
	setColor(p_renderer);
}

void Tile::setColor(SDL_Renderer * p_renderer)
{
	SDL_SetRenderDrawColor(p_renderer, 255, 255, 0, 255);
}
