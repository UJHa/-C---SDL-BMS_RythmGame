#pragma once
#include "SDL_image.h"
#include<vector>
using namespace std;
class Texture
{
protected:
	string _filePath;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;
	SDL_Texture* _texture;
public:
	Texture();
	Texture(const char* fileName);
	~Texture();
	void SetScale(float wScale, float hScale);
	void SetPosition(int x, int y);
	void Render();
	int GetRenderWidth();
	int GetRenderHeight();
	void SetHeight(int height);
	//AnimationSpeed info
protected:
	int _animationSpeed;
public:
	void SetAnimationSpeed(int aniSpd);
	int GetAnimationSpeed();

public:
	void SetNumberTexture(int index);
	//copy
public:
	void CopyTexture(Texture* texture);
	SDL_Rect GetSrcRect() { return _srcRect; }
	SDL_Rect GetDestRect() { return _destRect; }
	SDL_Texture* GetTexture() { return _texture; }
	string GetFileName() { return _filePath; }
};