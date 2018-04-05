#include "KeyboardEffectSprite.h"
#include "Texture.h"
KeyboardEffectSprite::KeyboardEffectSprite(string fileName) : Sprite(fileName)
{

}

KeyboardEffectSprite::~KeyboardEffectSprite()
{
}
void KeyboardEffectSprite::Init()
{
	Sprite::Init();
}
void KeyboardEffectSprite::Render()
{
	Sprite::Render();
}
void KeyboardEffectSprite::Update(int deltaTime)
{
}
void KeyboardEffectSprite::SetPosition(int x, int y)
{
	Sprite::SetPosition(x, y);
}
void KeyboardEffectSprite::SetNumber(int number)
{
	_frameDuration = 0;
	_renderTextureList.clear();
	vector<int> containCheck;
	while (0 != number)
	{
		containCheck.push_back(number % 10);

		_renderTextureList.push_back(_numberTextureList[number % 10]);
		number = number / 10;
	}
	int textureLength = _textureFrames[0]->GetRenderWidth() / 10;
	int textureStartPositionX = (_renderTextureList.size() - 1) * textureLength;
	textureStartPositionX /= 2;
	for (int i = 0; i < _renderTextureList.size(); i++)
	{
		_renderTextureList[i].SetPosition(_x + textureStartPositionX - i * textureLength, _y);
	}

	_isPlay = true;
}