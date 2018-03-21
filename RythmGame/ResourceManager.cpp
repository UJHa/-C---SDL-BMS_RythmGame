#include "ResourceManager.h"
#include "GameSystem.h"
using namespace std;
ResourceManager* ResourceManager::_instance = NULL;

ResourceManager* ResourceManager::GetInstance()
{
	if (_instance == NULL)
		_instance = new ResourceManager();
	return _instance;
}

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	map<string, SDL_Texture*>::iterator it;
	for (it = _textureMap.begin(); it != _textureMap.end(); it++)
	{
		delete it->second;
	}
	_textureMap.clear();
}
SDL_Texture* ResourceManager::FindTexture(string filePath)
{
	map<string, SDL_Texture*>::iterator it = _textureMap.find(filePath);
	if (it != _textureMap.end())
	{
		return it->second;
	}
	SDL_Texture* texture = IMG_LoadTexture(GameSystem::GetInstance()->GetSDLRenderer(), filePath.c_str());
	_textureMap[filePath] = texture;
	return texture;
}