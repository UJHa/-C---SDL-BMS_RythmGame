#include "NumbersSprite.h"
#include "DLinkedList.h"
#include "Texture.h"
NumbersSprite::NumbersSprite(string fileName) : Sprite(fileName)
{

}

NumbersSprite::~NumbersSprite()
{
}
void NumbersSprite::Render()
{
	if (false == _isPlay)
		return;
	for (vector<Texture*>::iterator it = _numberTextureList.begin(); it != _numberTextureList.end(); it++)
	{
		(*it)->Render();
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
				_numberTextureList.clear();
			}
		}
	}
	texture = _textureFrames[_frame];
	texture->SetPosition(_x, _y);

	int textureLength = texture->GetRenderWidth() / 10;
	int textureStartPositionX = -(_numberTextureList.size() - 1) * textureLength;
	textureStartPositionX /= 2;
	for (int i = 0; i < _numberTextureList.size(); i++)
	{
		_numberTextureList[i]->SetPosition(_x + textureStartPositionX + i * textureLength , _y);
	}
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
	_numberTextureList.clear();
	vector<Texture*> reverseList;
	while (0 != number)
	{
		Texture* texture = new Texture();
		texture->CopyTexture(_textureFrames[0]);
		texture->SetNumberTexture(number % 10);
		reverseList.push_back(texture);
		number = number / 10;
	}
	for (int i = 0; i < reverseList.size(); i++)
	{
		_numberTextureList.push_back(reverseList[reverseList.size() - 1 - i]);
	}
	_isPlay = true;
}