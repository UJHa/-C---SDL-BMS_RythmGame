#include "GameSystem.h"
#include <stdio.h>
#include "SDL.h"
#include "Font.h"
GameSystem* GameSystem::_instance = NULL;
GameSystem* GameSystem::GetInstance()
{
	if (_instance == NULL)
		_instance = new GameSystem();
	return _instance;
}
GameSystem::GameSystem()
{
}

GameSystem::~GameSystem()
{
}
int GameSystem::GetWidth()
{
	return 1280;
}
int GameSystem::GetHeight()
{
	return 800;
}
void GameSystem::Quit()
{
	SDL_Event quitEvent;
	quitEvent.type = SDL_QUIT;
	SDL_PushEvent(&quitEvent);
}

void GameSystem::SetSDLRenderer(SDL_Renderer* sdlRenderer)
{
	_sdlRenderer = sdlRenderer;
}
SDL_Renderer* GameSystem::GetSDLRenderer()
{
	return _sdlRenderer;
}