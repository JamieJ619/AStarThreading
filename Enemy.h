#pragma once
#include <SDL.h>

class Enemy
{
public:
	Enemy(int x, int y, int width, int height, SDL_Texture* texture, int tileTypeID);
	~Enemy();
	void render(SDL_Renderer * p_renderer, SDL_Point p_cameraPosition);
private:
	SDL_Texture* m_texture;
	SDL_Rect m_tileRect;
	int m_tileTypeID;


};

