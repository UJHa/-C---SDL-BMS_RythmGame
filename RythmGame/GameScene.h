#pragma once
#include<vector>
#include "Scene.h"
//#include "Track.h"
class Sprite;
class SDL_Texture;
class Font;
class TrackManager;
class ParsingBMS;
class NumbersSprite;
class GameScene : public Scene
{
private:
	Sprite * _backgroundSprite;
	TrackManager* _trackManager;
	int _gameDuration;
	Sprite* _trackListSprite;
	Sprite* _collisionSprite;
	NumbersSprite* _numberFontSprite;
public:
	GameScene();
	~GameScene();

	void Init();
	void Dinit();
	void Update(int deltaTime);
	void Render();
	//Input
	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
};