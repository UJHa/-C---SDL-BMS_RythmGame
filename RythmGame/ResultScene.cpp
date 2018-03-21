#include "ResultScene.h"
#include<stdio.h>
#include"SceneManager.h"
#include"GameSystem.h"
#include "SDL.h"
#include "Font.h"
#include "SettingGamePlay.h"
ResultScene::ResultScene()
{
	_fontList.clear();
	_focusFont = NULL;
}

ResultScene::~ResultScene()
{

	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}
	for (int i = 0; i < _fontList.size(); i++)
	{
		delete _fontList[i];
	}
	_fontList.clear();
	if (NULL != _focusFont)
	{
		delete _focusFont;
		_focusFont = NULL;
	}
}
void ResultScene::Init()
{
	_backgroundSprite = new Sprite("backgroundLogospr.csv");
	_backgroundSprite->Init();

	_focusCheck = eSelectTextType::REPLAY;
	int posX = GameSystem::GetInstance()->GetWidth() / 2;
	int posY = GameSystem::GetInstance()->GetHeight() / 2;
	string finishStr = SettingGamePlay::GetInstance()->GetBMS() + " Clear!";
	Font* musicNameFont = new Font("arialbd.ttf", 24);
	musicNameFont->SetText(finishStr.c_str(), 0, 0, 0);
	musicNameFont->SetPosition(posX, posY - 300);

	char scoreStr[256];
	sprintf(scoreStr, "Score : 0000");
	Font* scoreFont = new Font("arialbd.ttf", 24);
	scoreFont->SetText(scoreStr, 0, 0, 0);
	scoreFont->SetPosition(posX - 200, posY - 100);

	char maxComboStr[256];
	sprintf(maxComboStr, "Max Combo : %d", SettingGamePlay::GetInstance()->GetMaxComboNum());
	Font* maxComboFont = new Font("arialbd.ttf", 24);
	maxComboFont->SetText(maxComboStr, 0, 0, 0);
	maxComboFont->SetPosition(posX + 200, posY - 100);

	char greatInfoStr[256];
	sprintf(greatInfoStr, "GREAT : %d", SettingGamePlay::GetInstance()->GetJudgeCount(0));
	Font* greatFont = new Font("arialbd.ttf", 24);
	greatFont->SetText(greatInfoStr, 0, 0, 0);
	greatFont->SetPosition(posX - 300, posY + 100);

	char goodInfoStr[256];
	sprintf(goodInfoStr, "GOOD : %d", SettingGamePlay::GetInstance()->GetJudgeCount(1));
	Font* goodFont = new Font("arialbd.ttf", 24);
	goodFont->SetText(goodInfoStr, 0, 0, 0);
	goodFont->SetPosition(posX - 100, posY + 100);

	char badInfoStr[256];
	sprintf(badInfoStr, "BAD : %d", SettingGamePlay::GetInstance()->GetJudgeCount(2));
	Font* badFont = new Font("arialbd.ttf", 24);
	badFont->SetText(badInfoStr, 0, 0, 0);
	badFont->SetPosition(posX + 100, posY + 100);

	char poorInfoStr[256];
	sprintf(poorInfoStr, "POOR : %d", SettingGamePlay::GetInstance()->GetJudgeCount(3));
	Font* poorFont = new Font("arialbd.ttf", 24);
	poorFont->SetText(poorInfoStr, 0, 0, 0);
	poorFont->SetPosition(posX + 300, posY + 100);

	Font* replayFont = new Font("arialbd.ttf", 24);
	replayFont->SetText("REPLAY?", 0, 0, 0);
	replayFont->SetPosition(posX - 300, posY + 200);

	Font* toTitleFont = new Font("arialbd.ttf", 24);
	toTitleFont->SetText("TO TITLE?", 0, 0, 0);
	toTitleFont->SetPosition(posX, posY + 200);

	Font* quitFont = new Font("arialbd.ttf", 24);
	quitFont->SetText("QUIT?", 0, 0, 0);
	quitFont->SetPosition(posX + 300, posY + 200);

	_fontList.push_back(musicNameFont);
	_fontList.push_back(scoreFont);
	_fontList.push_back(maxComboFont);

	_fontList.push_back(greatFont);
	_fontList.push_back(goodFont);
	_fontList.push_back(badFont);
	_fontList.push_back(poorFont);

	//_fontList.push_back(focusFont);
	_fontList.push_back(replayFont);
	_fontList.push_back(toTitleFont);
	_fontList.push_back(quitFont);

	_focusFont = new Font("arialbd.ttf", 24);
	_focusFont->SetText("-                    -", 0, 0, 0);
	_focusFont->SetPosition(posX - 300, posY + 200);
}
void ResultScene::Dinit()
{
}
void ResultScene::Update(int deltaTime)
{
	_backgroundSprite->Update(deltaTime);
	for (int i = 0; i < _fontList.size(); i++)
	{
		_fontList[i]->Update(deltaTime);
	}
	_focusFont->Update(deltaTime);
}
void ResultScene::Render()
{
	_backgroundSprite->Render();
	for (int i = 0; i < _fontList.size(); i++)
	{
		_fontList[i]->Render();
	}
	_focusFont->Render();
}
void ResultScene::KeyUp(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_SPACE:
		SettingGamePlay::GetInstance()->Dinit();
		switch (_focusCheck)
		{
		case REPLAY:
			SettingGamePlay::GetInstance()->ResetData();
			SceneManager::GetInstance()->ChangeScene(eScene::SCENE_LOADING);
			printf("REPLAY\n");
			break;
		case TO_TITLE:
			SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE);
			printf("TITLE\n");
			break;
		case QUIT:
			SDL_Event quitEvent;
			quitEvent.type = SDL_QUIT;
			SDL_PushEvent(&quitEvent);
			printf("QUIT\n");
			break;
		}
		break;
	case SDLK_LEFT:
		if (_focusCheck > eSelectTextType::REPLAY)
		{
			_focusFont->MovePosition(-300, 0);
			_focusCheck = eSelectTextType(_focusCheck - 1);
		}
		break;
	case SDLK_RIGHT:
		if (_focusCheck < eSelectTextType::QUIT)
		{
			_focusFont->MovePosition(300, 0);
			_focusCheck = eSelectTextType(_focusCheck + 1);
		}
		break;
	default:
		break;
	}
}