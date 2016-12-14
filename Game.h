#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include <SDL.h>
#include "Tile.h"
#include <vector>
#include "TextureLoader.h"
#include "AStar.h"
#include "Enemy.h"
#include "ThreadPool.h"
#include "Player.h"

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
	void ThreadedAStar(int index);
	void LoadEnemies();
	void LoadMap();

private:
	bool m_running;
	SDL_Window* m_p_Window;
	SDL_Renderer* m_p_Renderer;
	SDL_Texture* m_p_Texture;
	SDL_Rect m_Source;
	SDL_Rect m_Destination;
	SDL_Surface* m_p_Surface;

	//	Grid
	int m_mapSize;
	const static int GRID_SIZE = 1000000;
	const static int ROW_SIZE_LARGE = 1000;
	const static int ROW_SIZE_SMALL = 100;
	const int TILE_SIZE = 25;
	const SDL_Point MAX_TILES = { 32, 24 };
	const int MAX_AREA = 768;
	std::vector<Tile*> m_tiles;
	int m_wallsPerTile;
	const int GAP_BETWEEN_WALLS = 47;

	AStar m_aStar;
	bool m_runAstar;
	
	Player m_player;
	std::vector<Enemy*> m_enemy;
	int m_numOfEnemies;

	int m_rowSize;
	bool m_canLoadEnemies;
	bool m_loadedEnemies;
	bool m_loadedMap;

	//	Camera
	SDL_Rect m_camera;
	SDL_Texture* m_tileAtlas;

	ThreadPool* m_thread_pool;
	bool m_isThreadingEnabled;

	SDL_mutex* m_locked;
};
#endif