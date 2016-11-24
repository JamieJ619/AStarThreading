#include "Game.h"
#include <iostream>
#include <thread>
#include <SDL_image.h>


using namespace std;

Game::Game() : m_running(false)
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

	int x = 0;
	int y = 0;
	for (int i = 0; i < MAX_AREA; i++)
	{
		m_tiles[x + y]->render(m_p_Renderer);
		x++;
		if (x == MAX_TILES.x)
		{
			y += 1000;
			x = 0;
		}
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
					break;
				case SDLK_DOWN:
					DEBUG_MSG("Down Key Pressed");
					break;
				case SDLK_LEFT:
					DEBUG_MSG("Left Key Pressed");
					break;
				case SDLK_RIGHT:
					DEBUG_MSG("Right Key Pressed");
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