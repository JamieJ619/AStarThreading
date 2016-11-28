#include "Game.h"
#include <iostream>
#include <thread>
#include <SDL_image.h>


using namespace std;

Game::Game() 
	: m_running(false),
	  m_camera{0,0,800,600}
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
			//DEBUG_MSG("Window creation success");
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
	SDL_Texture* tileTexture = TextureLoader::loadTexture("assets/tile.png", m_p_Renderer);
	SDL_Texture* wallTexture = TextureLoader::loadTexture("assets/wall.png", m_p_Renderer);

	int x = 0;
	int y = 0;
	int wallcounter = 1;
	int count = 0;

	for(int i = 0; i < GRID_SIZE; i++)
	{
		if (i % ROW_SIZE % 10 == 0 && i % ROW_SIZE != 0 && (y > 0 && y < ROW_SIZE - 1))
		{
			m_tiles.push_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, i, wallTexture));
		}
		else if(i % ROW_SIZE % 10 == 0 && i % ROW_SIZE != 0 && (y == 0 || y == ROW_SIZE -1))
		{
			count++;
			if (count % 2 == 0)
			{
				m_tiles.push_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, i, tileTexture));
			}
			else
			{
				m_tiles.push_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, i, wallTexture));
			}
		}
		else
		{
			m_tiles.push_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, i, tileTexture));
		}
		x++;
		if (x == ROW_SIZE)
		{
			y++;
			x = 0;
		}
		
	}
}

void Game::Render()
{	
	SDL_RenderClear(m_p_Renderer);

	// X and Y positions of camera in tiles
	int x = m_camera.x / TILE_SIZE;
	int y = (m_camera.y / TILE_SIZE) * ROW_SIZE;

	//	Tiles moved across
	int xCounter = x;
	int lastNodeX = x + MAX_TILES.x - 1;

	SDL_Point temp{ m_camera.x, m_camera.y };

	for (int i = 0; i < MAX_AREA; i++)
	{
		if (xCounter > lastNodeX)
		{
			y += ROW_SIZE;
			xCounter = x;
		}

		int currNode = xCounter + y;
		m_tiles[currNode]->render(m_p_Renderer, temp);
		xCounter++;
	}

	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
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
				case SDLK_UP:
					DEBUG_MSG("Up Key Pressed");
					//	Only move up when not at ypos 0
					if (m_camera.y > 0)
					{
						//m_camera.y -= TILE_SIZE;
						m_camera.y = 24000;
					}
					cout << m_camera.y << endl;
					break;
				case SDLK_DOWN:
					DEBUG_MSG("Down Key Pressed");
					if (m_camera.y < 25000 - 600)
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
					if (m_camera.x < 25000 - 800)
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
