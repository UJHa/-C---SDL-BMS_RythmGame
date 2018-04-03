#pragma once
#include "Sprite.h"
class NumbersSprite : public Sprite
{
private:
	vector<Texture> _renderTextureList;
	vector<Texture> _numberTextureList;
public:
	NumbersSprite(string fileName);
	~NumbersSprite();
	void Init();
	void Render();
	void Update(int deltaTime);
	void SetPosition(int x, int y);
	void SetNumber(int number);
};