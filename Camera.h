#pragma once
#include <SDL.h>

class Camera
{
public:
	Camera();
	~Camera();
private:
	SDL_Point m_posititon;
};

