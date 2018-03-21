#pragma once
#include "Scene.h"
class Sprite;
class Font;
class LoadingScene : public Scene
{
private:
	Sprite* _backgroundSprite;
	Font* _textFont;
public:
	LoadingScene();
	~LoadingScene();
public:
	void Init();
	void Dinit();
	void Update(int deltaTime);
	void Render();
};