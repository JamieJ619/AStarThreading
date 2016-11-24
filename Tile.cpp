#include "Tile.h"
#include <cstdlib>


Tile::Tile(int p_x, int p_y, int p_width, int p_height, int p_id, SDL_Texture* p_texture)
{
	m_tileRect = { p_x, p_y, p_width, p_height};
	m_texture = p_texture;
}


Tile::~Tile()
{

}

void Tile::render(SDL_Renderer * p_renderer, SDL_Point p_cameraPosition)
{
	SDL_Rect temp{ m_tileRect.x - p_cameraPosition.x, m_tileRect.y - p_cameraPosition.y, m_tileRect.w, m_tileRect.h };
	//SDL_RenderFillRect(p_renderer, &temp);
	SDL_RenderCopy(p_renderer, m_texture, NULL, &temp);
}

void Tile::setColor(SDL_Renderer * p_renderer)
{
	//SDL_SetRenderDrawColor(p_renderer, 255, 255, 0, 255);
	SDL_RenderCopy(p_renderer, m_texture, NULL, &m_tileRect);
}
