#include <stdio.h>
#include "Texture.h"
#include "SDL_image.h"
#include "GameSystem.h"
#include "ResourceManager.h"
Texture::Texture()
{

}
Texture::Texture(const char* fileName)
{
	char filePath[256];
	sprintf(filePath, "../Resources/Images/%s", fileName);
	_filePath = filePath;
	_texture = ResourceManager::GetInstance()->FindTexture(filePath);
	SDL_QueryTexture(_texture, NULL, NULL, &_srcRect.w, &_srcRect.h);
	
	_srcRect.x = 0;
	_srcRect.y = 0;
	_destRect.x = 0;
	_destRect.y = 0;

	_destRect.w = _srcRect.w;
	_destRect.h = _srcRect.h;
	_animationSpeed = 30;
}
Texture::~Texture()
{

}
void Texture::SetScale(float wScale, float hScale)
{
	_destRect.w = _srcRect.w * wScale;
	_destRect.h = _srcRect.h * hScale;
}
void Texture::SetPosition(int x, int y)
{
	_destRect.x = x;
	_destRect.y = y;
}
void Texture::Render()
{
	SDL_RenderCopy(GameSystem::GetInstance()->GetSDLRenderer(), _texture, &_srcRect, &_destRect);
}
int Texture::GetRenderWidth()
{
	return _destRect.w;
}
int Texture::GetRenderHeight()
{
	return _destRect.h;
}
void Texture::SetHeight(int height) 
{
	_destRect.h = height;
}
void Texture::SetAnimationSpeed(int aniSpd)
{
	if(0 != aniSpd)
		_animationSpeed = aniSpd;
}
int Texture::GetAnimationSpeed()
{
	return _animationSpeed;
}
void Texture::SetNumberTexture(int index)
{
	_srcRect.w = _destRect.w / 10;
	_destRect.w = _srcRect.w;
	_srcRect.x = index * _destRect.w;
}
void Texture::CopyTexture(Texture* texture)
{
	_srcRect = texture->GetSrcRect();
	_destRect = texture->GetDestRect();
	_texture = texture->GetTexture();
	_animationSpeed = texture->GetAnimationSpeed();
}