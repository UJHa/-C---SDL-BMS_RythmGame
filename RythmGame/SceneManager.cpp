#include "SceneManager.h"
#include <stdio.h>
#include<string.h>
#include "GameScene.h"
#include "TitleScene.h"
#include "LogoScene.h"
#include "ResultScene.h"
#include "LoadingScene.h"
SceneManager* SceneManager::_instance = NULL;
SceneManager* SceneManager::GetInstance()
{
	if (_instance == NULL)
		_instance = new SceneManager();
	return _instance;
}
SceneManager::SceneManager()
{
	_scene = NULL;
}

SceneManager::~SceneManager()
{
	if (NULL != _scene)
	{
		_scene->Dinit();
	}
}
void SceneManager::ChangeScene(eScene scene)
{
	if (NULL != _scene)
	{
		_scene->Dinit();
		delete _scene;
	}
	switch (scene)
	{
	case eScene::SCENE_LOGO:
		_scene = new LogoScene();
		_scene->Init();
		break;
	case eScene::SCENE_TITLE:
		_scene = new TitleScene();
		_scene->Init();
		break;
	case eScene::SCENE_LOADING:
		_scene = new LoadingScene();
		_scene->Init();
		break;
	case eScene::SCENE_GAME:
		_scene = new GameScene();
		_scene->Init();
		break;
	case eScene::SCENE_RESULT:
		_scene = new ResultScene();
		_scene->Init();
		break;
	default:
		break;
	}
}
void SceneManager::Update(int deltaTime)
{
	_scene->Update(deltaTime);
}
void SceneManager::Render()
{
	_scene->Render();
}