#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Game.h"
#include <thread>
#include <string>

using namespace std;

class Process
{
public:
	Process(){}
	Process(const Game& game) : m_Game(game)
	{

	}
	~Process(){};
	void run()
	{
		while(m_Game.IsRunning())
		{
			//DEBUG_MSG("Thread Running");
		}
	}
private:
	Game m_Game;
};

int main(int argc, char** argv){


	Game* game = new Game();

	//Adjust screen positions as needed
	game->Initialize("DGPP Skelatol",300,100,800,600, SDL_WINDOW_INPUT_FOCUS);

	game->LoadContent();

	while(game->IsRunning())
	{
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	game->CleanUp();
	game->UnloadContent();


	system("PAUSE");
	return 0;
}

