#pragma once
#include "Sprite.h"
class KeyboardEffectSprite : public Sprite
{
private:
	vector<Texture> _renderTextureList;
	vector<Texture> _numberTextureList;
public:
	KeyboardEffectSprite(string fileName);
	~KeyboardEffectSprite();
	void Init();
	void Render();
	void Update(int deltaTime);
	void SetPosition(int x, int y);
	void SetNumber(int number);
};