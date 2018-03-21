#include<stdio.h>
#include<string.h>
#include<vector>
#include "GameScene.h"
#include "SDL_mixer.h"
#include "GameSystem.h"
#include "SettingGamePlay.h"
#include "Sprite.h"
#include "Font.h"
#include "SceneManager.h"
#include "TrackManager.h"
#include "ParsingBMS.h"
#include "Wav.h"
#include "NumbersSprite.h"
GameScene::GameScene()
{
	_backgroundSprite = NULL;
	_trackListSprite = NULL;
	_collisionSprite = NULL;
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

	Font* scoreFont = new Font("arialbd.ttf", 24);
	scoreFont->SetText("Combo 0000 Score 0000", 255, 255, 255);
	scoreFont->SetPosition(scoreFont->GetRenderWidth() / 2, scoreFont->GetRenderHeight() / 2);
	SettingGamePlay::GetInstance()->AppendFontList(scoreFont);

	_trackListSprite = new Sprite("trackListspr.csv");
	_trackListSprite->Init();

	_collisionSprite = new Sprite("collisionspr.csv");
	_collisionSprite->Init();
	_trackManager = new TrackManager();
	_trackManager->Init();


	_numberFontSprite = new NumbersSprite("numberfontspr.csv");
	_numberFontSprite->Init();

	SettingGamePlay::GetInstance()->SetNumberSprite(_numberFontSprite);

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
	if (NULL != _collisionSprite)
	{
		delete _collisionSprite;
		_collisionSprite = NULL;
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
	_collisionSprite->Update(deltaTime);
	_numberFontSprite->Update(deltaTime);
	for (int i = 0; i < eJudge::NONE; i++)
	{
		SettingGamePlay::GetInstance()->GetJudgeFont(i)->Update(deltaTime);
	}

	if (_gameDuration <= SettingGamePlay::GetInstance()->GetGameTimeTick() + SettingGamePlay::GetInstance()->GetGameLoadTime() * 1000 + 2000)
	{
		std::vector<Font*> fontList = SettingGamePlay::GetInstance()->GetFontList();
		for (std::vector<Font*>::iterator it = fontList.begin(); it != fontList.end(); it++)
		{
			(*it)->Update(deltaTime);
		}
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
	_collisionSprite->Render();
	_trackManager->Render();
	_numberFontSprite->Render();
	for (int i = 0; i < eJudge::NONE; i++)
	{
		SettingGamePlay::GetInstance()->GetJudgeFont(i)->Render();
	}
	std::vector<Font*> fontList = SettingGamePlay::GetInstance()->GetFontList();
	for (std::vector<Font*>::iterator it = fontList.begin(); it != fontList.end(); it++)
	{
		(*it)->Render();
	}
}
void GameScene::KeyDown(int keyCode)
{
	_trackManager->KeyDown(keyCode);
}
void GameScene::KeyUp(int keyCode)
{
	_trackManager->KeyUp(keyCode);
}