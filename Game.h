#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include <SDL.h>
#include "Tile.h"
#include <vector>
#include "TextureLoader.h"
#include "AStar.h"
#include "Enemy.h"

class Game
{
public:
	Game();
	~Game();
	bool Initialize(const char*, int, int, int, int, int);
	void LoadContent();
	void UnloadContent();
	void Render();
	void Update();
	void HandleEvents();
	bool IsRunning();
	void CleanUp();
	void Camera();
private:
	bool m_running;
	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;
	SDL_Texture* m_p_Texture;
	SDL_Rect m_Source;
	SDL_Rect m_Destination;
	SDL_Surface* m_p_Surface;

	//	Grid
	const static int GRID_SIZE = 1000000;
	const static int ROW_SIZE = 1000;
	const int TILE_SIZE = 25;
	const SDL_Point MAX_TILES = { 32, 24 };
	const int MAX_AREA = 768;
	std::vector<Tile*> m_tiles;
	int m_wallsPerTile;
	const int GAP_BETWEEN_WALLS = 49;

	AStar m_aStar;
	bool m_runAstar;
	

	std::vector<Enemy*> m_enemy;
	int NUM_OF_ENEMIES = 4;

	//	Camera
	SDL_Rect m_camera;
	SDL_Texture* m_tileAtlas;
};
#endif