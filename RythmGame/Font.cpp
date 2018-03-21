#include "Font.h"
#include "GameSystem.h"
#include<stdio.h>
Font::Font(const char * fileName, int fontSize)
{
	char filePath[256];
	sprintf(filePath, "../Resources/Font/%s", fileName);

	_sansFont = TTF_OpenFont(filePath, fontSize);
}

Font::~Font()
{

}
void Font::Update(int deltaTime)
{

}
void Font::SetPosition(int x, int y)
{
	_destRect.x = x - _destRect.w / 2;
	_destRect.y = y - _destRect.h / 2;
}
void Font::SetText(const char* text , int red, int green, int blue)
{
	SDL_Color color = { red,green,blue };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_sansFont, text, color);
	_texture = SDL_CreateTextureFromSurface(GameSystem::GetInstance()->GetSDLRenderer(), surfaceMessage);

	SDL_QueryTexture(_texture, NULL, NULL, &_srcRect.w, &_srcRect.h);

	_srcRect.x = 0;
	_srcRect.y = 0;

	_destRect.w = _srcRect.w;
	_destRect.h = _srcRect.h;
}
void Font::MovePosition(int x, int y)
{
	_destRect.x += x;
	_destRect.y += y;
}