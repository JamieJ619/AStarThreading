#pragma once
#include <SDL.h>

class Tile
{
public:
	Tile(int x, int y, int width, int height, int id, SDL_Texture* texture, bool isWall, int p_tileTypeID);
	~Tile();

	void render(SDL_Renderer * renderer, SDL_Point cameraPos);
	void setColor(SDL_Renderer * renderer);


	void setID(bool p_id);
	int getID();



	void setIsWall(bool isWall);
	bool getIsWall();

	void setTileTypeID(int typeID);

	SDL_Point getPosition();

private:
	SDL_Rect m_tileRect;
	SDL_Texture* m_texture;
	int m_tileID;
	// A Star

	int m_tileTypeID;

	bool m_isWall;
};

