#pragma once
struct SDL_Renderer;
class Font;
class GameSystem
{
//Singleton
private:
	static GameSystem* _instance;
public:
	static GameSystem* GetInstance();
private:
	GameSystem();
public:
	~GameSystem();
private:
	SDL_Renderer* _sdlRenderer;
	//Win Info
public:
	int GetWidth();
	int GetHeight();
	void Quit();

	void SetSDLRenderer(SDL_Renderer* sdlRenderer);
	SDL_Renderer* GetSDLRenderer();
};