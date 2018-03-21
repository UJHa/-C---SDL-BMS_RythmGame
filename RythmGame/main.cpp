#include "SDL.h"
#include "SDL_image.h"
#include "GameSystem.h"
#include"SDL_ttf.h"
#include<stdio.h>
#include<stdlib.h>
#include "SceneManager.h"
int main(int argc, char* argv[])
{
	int winWidth = GameSystem::GetInstance()->GetWidth();
	int winHeight = GameSystem::GetInstance()->GetHeight();
	//set sdl
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);
	SDL_Window* sdlWindow = SDL_CreateWindow("Title name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_OPENGL);
	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, 0, 0);
	
	//set font
	if (TTF_Init() < 0)
	{
		printf("TTF Error\n");
	}
	atexit(TTF_Quit);

	GameSystem::GetInstance()->SetSDLRenderer(sdlRenderer);
	
	SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);

	SceneManager::GetInstance()->ChangeScene(eScene::SCENE_LOGO);

	SDL_Event sdlEvent;

	int frame = 0;
	int oldframe = 0;
	int curtick = SDL_GetTicks();
	int oldtick = curtick;
	while (1)
	{
		curtick = SDL_GetTicks();
		frame = (SDL_GetTicks() % 1000) * 60;	//60 frame
		frame /= 1000;
		if (oldframe != frame)
		{
			int deltaTime = curtick - oldtick;
			oldtick = curtick;
			oldframe = frame;
			if (SDL_PollEvent(&sdlEvent))
			{
				if (SDL_QUIT == sdlEvent.type)
					break;

				if (SDL_KEYUP == sdlEvent.type)
				{
					if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
					{
						SDL_Event quitEvent;
						quitEvent.type = SDL_QUIT;
						SDL_PushEvent(&quitEvent);
					}
					SceneManager::GetInstance()->KeyUp(sdlEvent.key.keysym.sym);
				}
				if (SDL_KEYDOWN == sdlEvent.type)
				{
					SceneManager::GetInstance()->KeyDown(sdlEvent.key.keysym.sym);
					
				}
			}
			SceneManager::GetInstance()->Update(deltaTime);

			SDL_RenderClear(sdlRenderer);
	
			SceneManager::GetInstance()->Render();

			SDL_RenderPresent(sdlRenderer);
		}
	}
	return 0;
}