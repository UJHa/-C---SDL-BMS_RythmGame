#include "LogoScene.h"
#include<stdio.h>
#include<SDL.h>
#include"SceneManager.h"
#include"GameSystem.h"
#include "Font.h"
#include "Sprite.h"
LogoScene::LogoScene()
{
	_backgroundSprite = NULL;
	_textFont = NULL;
}

LogoScene::~LogoScene()
{
	if (NULL != _textFont)
	{
		delete _textFont;
		_textFont = NULL;
	}
}
void LogoScene::Init()
{
	int posX = GameSystem::GetInstance()->GetWidth() / 2;
	int posY = GameSystem::GetInstance()->GetHeight() / 2;
	_textFont = new Font("arialbd.ttf", 24);
	_textFont->SetText("Welcome to BMS RythmGame!", 0, 0, 0);
	_textFont->SetPosition(posX , posY);

	_backgroundSprite = new Sprite("backgroundLogospr.csv");
	_backgroundSprite->Init();
	//_backgroundSprite->SetPosition(0,0);
}
void LogoScene::Dinit()
{
}
void LogoScene::Update(int deltaTime)
{
	_backgroundSprite->Update(deltaTime);
	_textFont->Update(deltaTime);
}
void LogoScene::Render()
{
	_backgroundSprite->Render();
	_textFont->Render();
}
void LogoScene::KeyUp(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_SPACE:
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE);
		break;
	default:
		break;
	}
}