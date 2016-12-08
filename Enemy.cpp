#include "Enemy.h"

Enemy::Enemy(int p_x, int p_y, int p_width, int p_height, SDL_Texture* p_texture, int p_tileTypeID)
	: m_tileTypeID(p_tileTypeID)
{
	m_tileRect = { p_x, p_y, p_width, p_height };
	m_texture = p_texture;
}

Enemy::~Enemy()
{
}

void Enemy::render(SDL_Renderer * p_renderer, SDL_Point p_cameraPosition)
{
	SDL_Rect temp{ m_tileRect.x - p_cameraPosition.x, m_tileRect.y - p_cameraPosition.y, m_tileRect.w, m_tileRect.h };
	SDL_Rect source{ m_tileTypeID * 100, 0, 100, 100 };
	SDL_RenderCopy(p_renderer, m_texture, &source, &temp);
}

void Enemy::setPath(std::vector<SDL_Point> p_path)
{
	m_path = p_path;
}

int Enemy::getTileIndex()
{
	m_tileIndex = m_tileRect.x / 25 + (m_tileRect.y / 25) * 1000;
	return m_tileIndex;
}
