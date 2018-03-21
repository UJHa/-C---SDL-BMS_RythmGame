#pragma once
#include "Scene.h"
struct Font;
struct Sprite;
class LogoScene : public Scene
{
private:
	Font* _textFont;
	Sprite* _backgroundSprite;
public:
	LogoScene();
	~LogoScene();
public:
	void Init();
	void Dinit();
	void Update(int deltaTime);
	void Render();
	void KeyUp(int keyCode);
};