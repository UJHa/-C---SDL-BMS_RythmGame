#include "Sprite.h"
#include "SDL_image.h"
#include "GameSystem.h"
#include "Texture.h"
#include <list>
Sprite::Sprite(string fileName)
{	
	_fileName = fileName;
}

Sprite::~Sprite()
{
}
void Sprite::Init()
{ 
	_frame = 0;
	_frameDuration = 0;
	_pivotX = 0.5f;
	_pivotY = 0.5f;

	char filePath[256];
	sprintf(filePath, "../Resources/%s", _fileName.c_str());


	FILE* fp = fopen(filePath, "r");
	if (NULL == fp)
	{
		printf("File 안열림 에러\n");
	}
	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);
	vector<string> spriteInfoNameList;
	spriteInfoNameList.clear();

	//첫줄 문자열 파싱
	char* token = strtok(record, ",");
	while (NULL != token )
	{
		spriteInfoNameList.push_back(token);
		//printf("%s\n", token);
		token = strtok(NULL, ",");
	}

	list<Texture*> textureFramesList;
	char* textureName;
	float scaleWidth, scaleHeight;
	int animationSpeed = 0;
	//스프라이트 정보 문자열 파싱
	while (true)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;
		{
			char* token = strtok(record, ",");
			for (vector<string>::iterator itr = spriteInfoNameList.begin();
				itr != spriteInfoNameList.end();
				itr++)
			{ 
				if (!(*itr).compare("fileName"))
				{ textureName = token; }
				if (!(*itr).compare("scaleWidth"))
				{ scaleWidth = atof(token); }
				if (!(*itr).compare("scaleHeight"))
				{ scaleHeight = atof(token); }
				else if (!(*itr).compare("positionX")) { _x = atoi(token); }
				else if (!(*itr).compare("positionY")){ _y = atoi(token); }
				else if (!(*itr).compare("pivotX")){ _pivotX = atof(token); }
				else if (!(*itr).compare("pivotY")){ _pivotY = atof(token); }
				else if (!(*itr).compare("isLoop")) { _isLoop = atoi(token); }
				else if (!(*itr).compare("aniSpeed")) 
 				{ animationSpeed = (int)(atof(token) * 1000); }
				token = strtok(NULL, ",");
			}
			if (_isLoop)
				_isPlay = true;
			else
				_isPlay = false;
			Texture* texture = new Texture(textureName);
			texture->SetScale(scaleWidth, scaleHeight);
			texture->SetAnimationSpeed(animationSpeed);
			textureFramesList.push_back(texture);
		}
	}
	fclose(fp);
	_frameMaxCount = textureFramesList.size();

	for (list<Texture*>::iterator itr = textureFramesList.begin();
		itr != textureFramesList.end();
		itr++)
	{
		Texture* texture = (*itr);
		_textureFrames.push_back(texture);
	}
	/*list<Texture*>::iterator itr = textureFramesList.begin();
	_x -= (*itr)->GetRenderWidth() * _pivotX;
	_y -= (*itr)->GetRenderHeight() * _pivotY;*/
	SetPosition(_x, _y);
}
void Sprite::Render()
{
	if (false == _isPlay)
		return;
	_textureFrames[_frame]->Render();
}
void Sprite::Update(int deltaTime)
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
			}
		}
	}
	texture = _textureFrames[_frame];
	texture->SetPosition(_x, _y);
}
void Sprite::SetPosition(int x, int y)
{
	Texture* texture = _textureFrames[_frame];
	if(0<=x)
		_x = x - texture->GetRenderWidth() * _pivotX;
	_y = y - texture->GetRenderHeight() * _pivotY;
	texture->SetPosition(_x, _y);
}
void Sprite::Play()
{
	_frame = 0;
	_isPlay = true;
}
void Sprite::Stop()
{
	_isPlay = false;
}
void Sprite::SetHeight(int height)
{
	Texture* texture = _textureFrames[_frame];
	texture->SetHeight(height);
}
void Sprite::SetPivotY(float pivotY)
{
	_pivotY = pivotY;
}
int Sprite::GetWidth()
{
	Texture* texture = _textureFrames[_frame];
	return texture->GetRenderWidth();
}
int Sprite::GetHeight()
{
	Texture* texture = _textureFrames[_frame];
	return texture->GetRenderHeight();
}
void Sprite::MovePosition(int x, int y)
{
	Texture* texture = _textureFrames[_frame];
	_x += x;
	_y += y;
	texture->SetPosition(_x, _y);
}