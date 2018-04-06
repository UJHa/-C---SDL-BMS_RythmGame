#pragma once
#include<map>
#include "Scene.h"
using namespace std;
class Sprite;
class TrackManager;
class NumbersSprite;
enum eTrackNum;
class GameScene : public Scene
{
private:
	Sprite * _backgroundSprite;
	TrackManager* _trackManager;
	int _gameDuration;
	Sprite* _trackListSprite;
	//Sprite* _collisionSprite;
	NumbersSprite* _numberFontSprite;
public:
	GameScene();
	~GameScene();

	void Init();
	void InitJudgeSprite();
	void Dinit();
	void Update(int deltaTime);
	void Render();
	//Input
	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
};