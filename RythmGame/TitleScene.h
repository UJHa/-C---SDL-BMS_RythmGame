#pragma once
#include "Scene.h"
#include "Sprite.h"
#include<list>
using namespace std;
enum eScene;
class MusicList;
class TitleScene : public Scene
{
private:
	Sprite* _backgroundSprite;
	Sprite* _selectBoxSprite;
public:
	TitleScene();
	~TitleScene();
public:
	void Init();
	void Dinit();
	void Update(int deltaTime);
	void Render();
	//music list sprite
private:
	MusicList* _musicList;
};