#pragma once
#include "Texture.h"
#include "sdl_ttf.h"
class Font : public Texture
{
private:
	TTF_Font* _sansFont;
public:
	Font(const char * fileName, int fontSize);
	~Font();
	void Update(int deltaTime);
	void SetPosition(int x, int y);
	void SetText(const char* text, int red, int green, int blue);
	void MovePosition(int x, int y);
};