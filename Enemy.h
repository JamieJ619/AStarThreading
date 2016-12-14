#pragma once
#include <SDL.h>
#include <vector>

class Enemy
{
public:
	Enemy(int x, int y, int width, int height, SDL_Texture* texture, int tileTypeID);
	~Enemy();
	void render(SDL_Renderer * p_renderer, SDL_Point p_cameraPosition);
	void setPath(std::vector<SDL_Point> path);
	void update();
	int getTileIndex();
	void setState(int state);
	int getState();
	bool m_finished;
private:
	SDL_Texture* m_texture;
	SDL_Rect m_tileRect;
	int m_tileTypeID;
	std::vector<SDL_Point> m_path;
	int m_tileIndex;
	int m_pathIndex;
	int m_state;
};

