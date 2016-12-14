#include "Enemy.h"

Enemy::Enemy(int p_x, int p_y, int p_width, int p_height, SDL_Texture* p_texture, int p_tileTypeID)
	: m_tileTypeID(p_tileTypeID),
	m_state(0),
	m_finished(false)
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

void Enemy::update()
{
	SDL_Point tempPath{ m_path[m_pathIndex].x, m_path[m_pathIndex].y };

	if (tempPath.x == m_tileRect.x && tempPath.y == m_tileRect.y)
	{
		if (m_pathIndex < m_path.size() -1)
		{
			m_pathIndex++;
		}
		else
		{
			m_finished = true;
			m_state = 0;
		}
	}
	if (!m_finished)
	{

		if (m_tileRect.x > tempPath.x)
		{
			m_tileRect.x -= 25;
		}
		else if (m_tileRect.x < tempPath.x)
		{
			m_tileRect.x += 25;
		}
		else if (m_tileRect.y < tempPath.y)
		{
			m_tileRect.y += 25;
		}
		else if (m_tileRect.y > tempPath.y)
		{
			m_tileRect.y -= 25;
		}
	}
}

int Enemy::getTileIndex()
{
	m_tileIndex = m_tileRect.x / 25 + (m_tileRect.y / 25) * 1000;
	return m_tileIndex;
}

void Enemy::setState(int p_state)
{
	m_state = p_state;
}

int Enemy::getState()
{
	return m_state;
}
