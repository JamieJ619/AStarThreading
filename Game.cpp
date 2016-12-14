#include "Game.h"
#include <iostream>
#include <thread>
#include <SDL_image.h>


using namespace std;

Game::Game() 
	: m_running(false),
	  m_camera{0,0,800,600},
	  m_wallsPerTile(50),
	  m_aStar(ROW_SIZE_LARGE, GRID_SIZE),
	  m_runAstar(false),
	  m_thread_pool(new ThreadPool()),
	  m_isThreadingEnabled(true),
	  m_canLoadEnemies(false),
	  m_loadedEnemies(false),
	  m_numOfEnemies(0),
	  m_player(50, 0, TILE_SIZE, TILE_SIZE, 5)
{

}

Game::~Game()
{
}

bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_p_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if(m_p_Window != 0)
		{
			m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, 0);
			if(m_p_Renderer != 0)
			{
				SDL_SetRenderDrawColor(m_p_Renderer, 255, 255, 255, 255);
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	m_running = true;

	return true;
}



void Game::LoadContent()
{
	DEBUG_MSG("Input number of enemies: ");
	std::cin >> m_numOfEnemies;
	DEBUG_MSG("Press 1 for LARGE map. \nPress 2 for SMALL map. \nPress ENTER to run A*");

	m_tileAtlas = TextureLoader::loadTexture("assets/TileAtlas.png", m_p_Renderer);
	m_player.setTexture(m_tileAtlas);
	//m_enemy.push_back(new Enemy(75, 250, TILE_SIZE, TILE_SIZE, m_tileAtlas, 4));

	LoadMap();
}

void Game::Render()
{	
	SDL_RenderClear(m_p_Renderer);

	// X and Y positions of camera in tiles
	int x = m_camera.x / TILE_SIZE;
	int y = (m_camera.y / TILE_SIZE) * ROW_SIZE_LARGE;

	//	Tiles moved across
	int xCounter = x;
	int lastNodeX = x + MAX_TILES.x - 1;

	SDL_Point temp{ m_camera.x, m_camera.y };

	for (int i = 0; i < MAX_AREA; i++)

	{
		if (xCounter > lastNodeX)
		{
			y += ROW_SIZE_LARGE;
			xCounter = x;
		}

		int currNode = xCounter + y;
		m_tiles[currNode]->render(m_p_Renderer, temp);
		xCounter++;
	}

	if (m_loadedEnemies)
	{
		for (int i = 0; i < m_numOfEnemies; i++)
		{
			m_enemy[i]->render(m_p_Renderer, temp);
		}

	}
	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
	if (m_runAstar && m_loadedEnemies)
	{
		for (int i = 0; i < m_numOfEnemies; i++)
		{
			if (m_enemy[i]->getState() == 0 && m_enemy[i]->m_finished != true)
			{
				if (m_isThreadingEnabled == true)
				{
					m_thread_pool->AddTask(std::bind(&Game::ThreadedAStar, this, i));
				}
				else
				{
					m_enemy[i]->setPath(m_aStar.search(&m_tiles, 2, m_enemy[i]->getTileIndex()));
				}
				m_enemy[i]->setState(1);
			}
			else if (m_enemy[i]->getState() == 2)
			{
				if (m_enemy[i]->m_finished == false)
				{
					m_enemy[i]->update();
				}
			}
		}
		//m_runAstar = false;
		/*int x = m_enemy[0]->getTileIndex();
		m_enemy[0]->setPath(m_aStar.search(&m_tiles, 0, m_enemy[0]->getTileIndex()));*/
	}
}

void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					m_running = false;
					break;
				case SDLK_RETURN:
					m_runAstar = true;
					break; 
				case SDLK_1:
					m_rowSize = ROW_SIZE_LARGE;
					LoadEnemies();
					m_loadedEnemies = true;
					break;
				case SDLK_2:
					m_rowSize = ROW_SIZE_SMALL;
					LoadEnemies();
					m_loadedEnemies = true;
					break;
				case SDLK_w:
					if (m_camera.y > 1000)
					{
						m_camera.y -= 1000;
					}
					cout << m_camera.y << endl;
					break;
				case SDLK_s:
					if (m_camera.y < 25000 - 1600)
					{
						m_camera.y += 1000;
					}
					cout << m_camera.y << endl;
					break;
				case SDLK_a:
					if (m_camera.x > 1000)
					{
						m_camera.x -= 1000;
					}
					cout << m_camera.x << endl;
					break;
				case SDLK_d:
					if (m_camera.x < 25000 - 1800)
					{
						m_camera.x += 1000;
					}
					cout << m_camera.x << endl;
					break;
				case SDLK_UP:
					DEBUG_MSG("Up Key Pressed");
					//	Only move up when not at ypos 0
					if (m_camera.y > 0)
					{
						m_camera.y -= TILE_SIZE;
						//m_camera.y = 24000;
					}
					cout << m_camera.y << endl;
					break;
				case SDLK_DOWN:
					DEBUG_MSG("Down Key Pressed");
					if (m_camera.y < (ROW_SIZE_LARGE * TILE_SIZE) - 600)
					{
						m_camera.y += TILE_SIZE;
					}
					cout << m_camera.y << endl;
					break;
				case SDLK_LEFT:
					DEBUG_MSG("Left Key Pressed");
					if (m_camera.x > 0)
					{
						m_camera.x -= TILE_SIZE;
					}
					cout << m_camera.x << endl;
					break;
				case SDLK_RIGHT:
					DEBUG_MSG("Right Key Pressed");
					if (m_camera.x < (m_rowSize * TILE_SIZE) - 800)
					{
						m_camera.x += TILE_SIZE;
					}
					cout << m_camera.x << endl;
					break;
				default:
					break;
				}
	}
}

bool Game::IsRunning()
{
	return m_running;
}

void Game::UnloadContent()
{
}

void Game::CleanUp()
{
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}

void Game::Camera()
{

}

void Game::ThreadedAStar(int index)
{
	std::vector<SDL_Point> temp = m_aStar.search(&m_tiles, 2, m_enemy[index]->getTileIndex());
	SDL_LockMutex(m_locked);
	m_enemy[index]->setPath(temp);
	m_enemy[index]->setState(2);
	SDL_UnlockMutex(m_locked);
	/*int x = m_enemy[0]->getTileIndex();
	m_enemy[0]->setPath(m_aStar.search(&m_tiles, 5, m_enemy[0]->getTileIndex()));*/
}

void Game::LoadEnemies()
{
	int enemyY = 0;
	int enemyX = 0;

	for (int i = 0; i < m_numOfEnemies; i++)
	{
		if (enemyX > GAP_BETWEEN_WALLS)
		{
			enemyX = 0;
			enemyY++;
		}
		if (enemyY > 0)
		{
			int x = 0;
		}
		m_enemy.push_back(new Enemy((m_rowSize * TILE_SIZE) - (enemyX + 2) * TILE_SIZE, enemyY * TILE_SIZE, TILE_SIZE, TILE_SIZE, m_tileAtlas, 4));
		//m_enemy.push_back(new Enemy((5 * TILE_SIZE) , 5 * TILE_SIZE, TILE_SIZE, TILE_SIZE, m_tileAtlas, 4));
		enemyX++;
	}

}

void Game::LoadMap()
{

	int x = 0;
	int y = 0;
	int count = 0;

	for (int i = 0; i < GRID_SIZE; i++)
	{
		if (i % ROW_SIZE_LARGE % m_wallsPerTile == 0 && i % ROW_SIZE_LARGE != 0 && (y > 0 && y < ROW_SIZE_LARGE - 1))
		{
			m_tiles.push_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, i, m_tileAtlas, true, 1));
		}
		else if (i % ROW_SIZE_LARGE % m_wallsPerTile == 0 && i % ROW_SIZE_LARGE != 0 && (y == 0 || y == ROW_SIZE_LARGE - 1))
		{
			if (i > ROW_SIZE_LARGE && 2 % count != 0)
			{
				count = 1;
			}
			count++;
			if (count % 2 == 0)
			{
				m_tiles.push_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, i, m_tileAtlas, false, 0));
			}
			else
			{
				m_tiles.push_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, i, m_tileAtlas, true, 1));
			}
		}
		else
		{
			m_tiles.push_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, i, m_tileAtlas, false, 0));
		}

		x++;
		if (x == ROW_SIZE_LARGE)
		{
			y++;
			x = 0;
		}

	}
}
