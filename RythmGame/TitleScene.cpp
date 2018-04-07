#include<stdio.h>
#include"TitleScene.h"
#include"GameSystem.h"
#include"SceneManager.h"
#include<SDL.h>
#include"Font.h"
#include"SettingGamePlay.h"
#include"MusicList.h"
#include"InputManager.h"
TitleScene::TitleScene()
{
	_backgroundSprite = NULL;
	_selectBoxSprite = NULL;
	_musicList = NULL;
}

TitleScene::~TitleScene()
{
}
void TitleScene::Init()
{
	_backgroundSprite = new Sprite("backgroundLogospr.csv");
	_backgroundSprite->Init();

	_selectBoxSprite = new Sprite("selectBoxspr.csv");
	_selectBoxSprite->Init();

	_musicList = new MusicList();
	_musicList->Init();


}
void TitleScene::Dinit()
{
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}
	if (NULL != _selectBoxSprite)
		{
			delete _selectBoxSprite;
			_selectBoxSprite = NULL;
		}
	if (NULL != _musicList)
	{
		delete _musicList;
		_musicList = NULL;
	}
}
void TitleScene::Update(int deltaTime)
{
	if (InputManager::GetInstance()->IsKeyUp(SDLK_SPACE))
	{
		if (_musicList->IsExtensionBMS()) {
			SettingGamePlay::GetInstance()->ResetData(_musicList->GetFileRoute(), _musicList->GetNameBMS());
			SceneManager::GetInstance()->ChangeScene(eScene::SCENE_LOADING);
			return;
		}
		_musicList->SelectEvent();
	}
	if (InputManager::GetInstance()->IsKeyUp(SDLK_UP))
	{
		if (_musicList->IncreaseIterator())
		{
			_musicList->SpriteListMovePosition(0, -120);
		}
	}
	if (InputManager::GetInstance()->IsKeyUp(SDLK_DOWN))
	{
		if (_musicList->DecreaseIterator())
		{
			_musicList->SpriteListMovePosition(0, 120);
		}
	}
	_backgroundSprite->Update(deltaTime);
	_selectBoxSprite->Update(deltaTime);
}
void TitleScene::Render()
{	
	_backgroundSprite->Render();
	_musicList->Render();
	_selectBoxSprite->Render();
}