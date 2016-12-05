#include "Tile.h"
#include <cstdlib>
#include <limits>


Tile::Tile(int p_x, int p_y, int p_width, int p_height, int p_id, SDL_Texture* p_texture, bool p_isWall, int p_tileTypeID)
	: m_tileID(p_id),
	m_isWall(p_isWall),
	m_tileTypeID(p_tileTypeID)
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
	SDL_Rect source{ m_tileTypeID * 100,0,100,100 };
	SDL_RenderCopy(p_renderer, m_texture, &source, &temp);
}

void Tile::setColor(SDL_Renderer * p_renderer)
{
	//SDL_SetRenderDrawColor(p_renderer, 255, 255, 0, 255);
	SDL_RenderCopy(p_renderer, m_texture, NULL, &m_tileRect);
}

void Tile::setID(bool p_id)
{
	m_tileID = p_id;
}
int Tile::getID()
{
	return m_tileID;
}

void Tile::setIsWall(bool isWall)
{
	m_isWall = isWall;
}

bool Tile::getIsWall()
{
	return m_isWall;
}

void Tile::setTileTypeID(int typeID)
{
	m_tileTypeID = typeID;
}

SDL_Point Tile::getPosition()
{
	return SDL_Point{ m_tileRect.x, m_tileRect.y };
}