#include "LoadingScene.h"
#include "SettingGamePlay.h"
#include "SceneManager.h"
#include "GameSystem.h"
#include "Sprite.h"
#include "Font.h"
LoadingScene::LoadingScene()
{
	_backgroundSprite = NULL;
	_textFont = NULL;
}

LoadingScene::~LoadingScene()
{
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}
	if (NULL != _textFont)
	{
		delete _textFont;
		_textFont = NULL;
	}
}
void LoadingScene::Init()
{
	_backgroundSprite = new Sprite("backgroundLogospr.csv");
	_backgroundSprite->Init();

	_textFont = new Font("arialbd.ttf", 24);
	_textFont->SetText("Loading...!", 0, 0, 0);
	_textFont->SetPosition(GameSystem::GetInstance()->GetWidth() / 2, GameSystem::GetInstance()->GetHeight() / 2);
}
void LoadingScene::Dinit()
{

}
void LoadingScene::Update(int deltaTime)
{
	_backgroundSprite->Update(deltaTime);
	_textFont->Update(deltaTime);
	if (true == SettingGamePlay::GetInstance()->SettingData(deltaTime))
	{
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_GAME);
	}
}
void LoadingScene::Render()
{
	_backgroundSprite->Render();
	//_backgroundSprite->Render();
	_textFont->Render();
}