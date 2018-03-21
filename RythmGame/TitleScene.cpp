#include <stdio.h>
#include "TitleScene.h"
#include "GameSystem.h"
#include "SceneManager.h"
#include "SDL.h"
#include "Font.h"
#include "SettingGamePlay.h"
#include "MusicList.h"
TitleScene::TitleScene()
{
	_backgroundSprite = NULL;
	_musicList = NULL;
}

TitleScene::~TitleScene()
{
}
void TitleScene::Init()
{
	_backgroundSprite = new Sprite("backgroundLogospr.csv");
	_backgroundSprite->Init();

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
	if (NULL != _musicList)
	{
		delete _musicList;
		_musicList = NULL;
	}
}
void TitleScene::Update(int deltaTime)
{
	_backgroundSprite->Update(deltaTime);
}
void TitleScene::Render()
{
	_backgroundSprite->Render();
	_musicList->Render();
}
void TitleScene::KeyUp(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_SPACE:
		if (_musicList->IsExtensionBMS()) {
			SettingGamePlay::GetInstance()->ResetData(_musicList->GetFileRoute(), _musicList->GetNameBMS());
			SceneManager::GetInstance()->ChangeScene(eScene::SCENE_LOADING);
			break;
		}
		_musicList->SelectEvent();
		break;
	case SDLK_UP:
		if (_musicList->IncreaseIterator())
		{
			_musicList->SpriteListMovePosition(0, -120);
		}
		break;
	case SDLK_DOWN:
		if (_musicList->DecreaseIterator())
		{
			_musicList->SpriteListMovePosition(0, 120);
		}
		break;
	}
}