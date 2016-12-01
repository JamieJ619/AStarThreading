#include "Tile.h"
#include <cstdlib>
#include <limits>


Tile::Tile(int p_x, int p_y, int p_width, int p_height, int p_id, SDL_Texture* p_texture, bool p_isWall, int p_tileTypeID)
	:m_open(false),
	m_close(false),
	m_tileID(p_id),
	m_fCost(std::numeric_limits<int>::max()),
	m_gCost(std::numeric_limits<int>::max()),
	m_previousTile(NULL),
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

void Tile::setOpen(bool p_open)
{
	m_open = p_open;
}
bool Tile::getOpen()
{
	return m_open;
}

void Tile::setClose(bool p_close)
{
	m_close = p_close;
}
bool Tile::getClose()
{
	return m_close;
}

void Tile::setID(bool p_id)
{
	m_tileID = p_id;
}
int Tile::getID()
{
	return m_tileID;
}

void Tile::setFCost(int p_fCost)
{
	m_fCost = p_fCost;
}
int Tile::getFCost()
{
	return m_fCost;
}

void Tile::setGCost(int p_gCost)
{
	m_gCost = p_gCost;
}
int Tile::getGCost()
{
	return m_gCost;
}

void Tile::setPrevTile(Tile * tile)
{
	m_previousTile = tile;
}

Tile * Tile::getPrevTile()
{
	return m_previousTile;
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
