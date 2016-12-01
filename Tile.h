#pragma once
#include <SDL.h>

class Tile
{
public:
	Tile(int x, int y, int width, int height, int id, SDL_Texture* texture);
	~Tile();

	void render(SDL_Renderer * renderer, SDL_Point cameraPos);
	void setColor(SDL_Renderer * renderer);

	void setOpen(bool open);
	bool getOpen();

	void setClose(bool close);
	bool getClose();

	void setID(bool p_id);
	int getID();

	void setFCost(bool p_fCost);
	int getFCost();

	void setGCost(bool p_gCost);
	int getGCost();
private:
	SDL_Rect m_tileRect;
	SDL_Texture* m_texture;

	// A Star
	Tile* m_previousTile;
	bool m_open;
	bool m_close;
	int m_tileID;
	int m_fCost;
	int m_gCost;
};

