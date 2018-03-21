#pragma once
#include "Scene.h"
#include "Sprite.h"
class Font;
enum eSelectTextType
{
	REPLAY,
	TO_TITLE,
	QUIT,
};
class ResultScene : public Scene
{
private:
	Sprite* _backgroundSprite;
	vector<Font*> _fontList;

	Font* _focusFont;

	eSelectTextType _focusCheck;
public:
	ResultScene();
	~ResultScene();
public:
	void Init();
	void Dinit();
	void Update(int deltaTime);
	void Render();
	void KeyUp(int keyCode);
};