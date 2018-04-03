#include "NumbersSprite.h"
#include "DLinkedList.h"
#include "Texture.h"
NumbersSprite::NumbersSprite(string fileName) : Sprite(fileName)
{

}

NumbersSprite::~NumbersSprite()
{
}
void NumbersSprite::Init()
{
	Sprite::Init();
	for (int i = 0; i < 10; i++)
	{
		Texture* texture = new Texture(_fileName.c_str());
		texture->CopyTexture(_textureFrames[0]);
		texture->SetNumberTexture(i);
		_numberTextureList.push_back(*texture);
	}
}
void NumbersSprite::Render()
{
	if (false == _isPlay)
		return;
	for (vector<Texture>::iterator it = _renderTextureList.begin(); it != _renderTextureList.end(); it++)
	{
		(*it).Render();
	}
}
void NumbersSprite::Update(int deltaTime)
{
	if (false == _isPlay)
		return;
	_frameDuration += deltaTime;
	Texture* texture = _textureFrames[_frame];
	if (texture->GetAnimationSpeed() < _frameDuration)
	{
		_frameDuration = 0;
		_frame = (_frame + 1) % _frameMaxCount;
		if (false == _isLoop)
		{
			if (0 == _frame)
			{
				_isPlay = false;
				_renderTextureList.clear();
			}
		}
	}
	texture = _textureFrames[_frame];
	texture->SetPosition(_x, _y);
}
void NumbersSprite::SetPosition(int x, int y)
{
	Texture* texture = _textureFrames[_frame];
	if (0 <= x)
		_x = x - texture->GetRenderWidth() / 10 * _pivotX;
	_y = y - texture->GetRenderHeight() / 10 * _pivotY;
	texture->SetPosition(_x, _y);
}
void NumbersSprite::SetNumber(int number)
{
	_frameDuration = 0;
	_renderTextureList.clear();
	vector<int> containCheck;
	while (0 != number)
	{
		containCheck.push_back(number % 10);
		/*Texture* texture = new Texture(_fileName.c_str());
		texture->CopyTexture(_textureFrames[0]);
		texture->SetNumberTexture(number % 10);*/
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