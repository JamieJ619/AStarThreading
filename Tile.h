#pragma once
#include <SDL.h>

class Tile
{
public:
	Tile(int x, int y, int width, int height, int id, SDL_Texture* texture, bool isWall, int p_tileTypeID);
	~Tile();

	void render(SDL_Renderer * renderer, SDL_Point cameraPos);
	void setColor(SDL_Renderer * renderer);

	void setOpen(bool open);
	bool getOpen();

	void setClose(bool close);
	bool getClose();

	void setID(bool p_id);
	int getID();

	void setFCost(int p_fCost);
	int getFCost();

	void setGCost(int p_gCost);
	int getGCost();

	void setPrevTile(Tile* tile);
	Tile* getPrevTile();

	void setIsWall(bool isWall);
	bool getIsWall();

	void setTileTypeID(int typeID);

	SDL_Point getPosition();

private:
	SDL_Rect m_tileRect;
	SDL_Texture* m_texture;
	int m_tileID;
	// A Star
	Tile* m_previousTile;
	bool m_open;
	bool m_close;
	int m_tileTypeID;
	int m_fCost;
	int m_gCost;
	bool m_isWall;
};

