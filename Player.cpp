#include "Player.h"



Player::Player(int p_x, int p_y, int p_width, int p_height, int p_tileTypeID)
{
	m_tileRect = { p_x, p_y, p_width, p_height };
	m_tileTypeID = p_tileTypeID;
}


Player::~Player()
{
}

void Player::render(SDL_Renderer * p_renderer, SDL_Point p_cameraPosition)
{
	SDL_Rect temp{ m_tileRect.x - p_cameraPosition.x, m_tileRect.y - p_cameraPosition.y, m_tileRect.w, m_tileRect.h };
	SDL_Rect source{ m_tileTypeID * 100, 0, 100, 100 };
	SDL_RenderCopy(p_renderer, m_texture, &source, &temp);
}

void Player::setTexture(SDL_Texture* p_texture)
{
	m_texture = p_texture;
}
