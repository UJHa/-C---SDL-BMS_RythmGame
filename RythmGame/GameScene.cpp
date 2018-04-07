#include<stdio.h>
#include<string.h>
#include "GameScene.h"
#include "SettingGamePlay.h"
#include "Sprite.h"
#include "Font.h"
#include "SceneManager.h"
#include "TrackManager.h"
#include "Wav.h"
#include "NumbersSprite.h"
#include "InputManager.h"
GameScene::GameScene()
{
	_backgroundSprite = NULL;
	_trackListSprite = NULL;
	_trackManager = NULL;
	_gameDuration = 0;
}

GameScene::~GameScene()
{
	 
}
void GameScene::Init()
{
	_backgroundSprite = new Sprite("backgroundGamespr.csv");
	_backgroundSprite->Init();

	_trackListSprite = new Sprite("trackListspr.csv");
	_trackListSprite->Init();

	_trackManager = new TrackManager();
	_trackManager->Init();

	_numberFontSprite = new NumbersSprite("numberfontspr.csv");
	_numberFontSprite->Init();

	SettingGamePlay::GetInstance()->SetNumberSprite(_numberFontSprite);

	InitJudgeSprite();
}
void GameScene::InitJudgeSprite()
{
	Sprite* greatSprite = new Sprite("judgeGreatspr.csv");
	Sprite* goodSprite = new Sprite("judgeGoodspr.csv");
	Sprite* badSprite = new Sprite("judgeBadspr.csv");
	Sprite* poorSprite = new Sprite("judgePoorspr.csv");
	greatSprite->Init();
	goodSprite->Init();
	badSprite->Init();
	poorSprite->Init();
	SettingGamePlay::GetInstance()->AddJudgeFont(greatSprite);
	SettingGamePlay::GetInstance()->AddJudgeFont(goodSprite);
	SettingGamePlay::GetInstance()->AddJudgeFont(badSprite);
	SettingGamePlay::GetInstance()->AddJudgeFont(poorSprite);
}
void GameScene::Dinit()
{
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}
	if (NULL != _trackManager)
	{
		_trackManager->Dinit();
		delete _trackManager;
		_trackManager = NULL;
	}
	if (NULL != _trackListSprite)
	{
		delete _trackListSprite;
		_trackListSprite = NULL;
	}
	if (NULL != _numberFontSprite)
	{
		delete _numberFontSprite;
		_numberFontSprite = NULL;
	}
}
void GameScene::Update(int deltaTime)
{
	_backgroundSprite->Update(deltaTime);
	_trackListSprite->Update(deltaTime);
	_numberFontSprite->Update(deltaTime);
	for (int i = 0; i < eJudge::NONE; i++)
	{
		SettingGamePlay::GetInstance()->GetJudgeFont(i)->Update(deltaTime);
	}

	if (_gameDuration <= SettingGamePlay::GetInstance()->GetGameTimeTick() + SettingGamePlay::GetInstance()->GetGameLoadTime() * 1000 + 2000)
	{
		_trackManager->Update(deltaTime);
		std::vector<Wav*> wavList = SettingGamePlay::GetInstance()->GetWavList();
		for (std::vector<Wav*>::iterator it = wavList.begin(); it != wavList.end(); it++)
		{
			(*it)->Update(deltaTime);
		}
		_gameDuration += deltaTime;
	}
	else
	{
		SettingGamePlay::GetInstance()->Dinit();
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_RESULT);
	}
}
void GameScene::Render()
{
	_backgroundSprite->Render();
	_trackListSprite->Render();
	_trackManager->Render();
	_numberFontSprite->Render();
	for (int i = 0; i < eJudge::NONE; i++)
	{
		SettingGamePlay::GetInstance()->GetJudgeFont(i)->Render();
	}
}
void GameScene::KeyDown(int keyCode)
{
	//InputManager::GetInstance()->KeyDown(keyCode);
}
void GameScene::KeyUp(int keyCode)
{
	//InputManager::GetInstance()->KeyUp(keyCode);
}