#pragma once
#include <SDL.h>
#include <vector>

class Player
{
public:
	Player(int p_x, int p_y, int p_width, int p_height, int p_tileTypeID);
	~Player();
	void render(SDL_Renderer * p_renderer, SDL_Point p_cameraPosition);
	void setTexture(SDL_Texture* tex);
private:
	SDL_Texture* m_texture;
	SDL_Rect m_tileRect;
	int m_tileTypeID;
};

