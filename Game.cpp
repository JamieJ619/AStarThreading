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
	int x = 0;
	int y = 0;

	for(int i = 0; i < GRID_SIZE; i++)
	{
		m_tiles.push_back(new Tile(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, i));
		x++;
		if (x == ROW_SIZE )
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
	int xCounter = 0;
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
						m_camera.y -= TILE_SIZE;
					}
					break;
				case SDLK_DOWN:
					DEBUG_MSG("Down Key Pressed");
					m_camera.y += TILE_SIZE;
					break;
				case SDLK_LEFT:
					DEBUG_MSG("Left Key Pressed");
					if (m_camera.y > 0)
					{
						m_camera.x -= TILE_SIZE;
					}
					break;
				case SDLK_RIGHT:
					DEBUG_MSG("Right Key Pressed");
					m_camera.x += TILE_SIZE;
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
