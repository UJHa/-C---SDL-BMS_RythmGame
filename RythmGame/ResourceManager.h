#pragma once
#include <map>
#include "SDL_image.h"
class ResourceManager
{
//singleton
private:
	static ResourceManager* _instance;
public:
	static ResourceManager* GetInstance();

private:
	ResourceManager();
//texture Resource
private:
	std::map<std::string, SDL_Texture*> _textureMap;
public:
	~ResourceManager();
	SDL_Texture* FindTexture(std::string filePath);
};