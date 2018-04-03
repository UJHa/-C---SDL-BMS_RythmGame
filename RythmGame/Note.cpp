#include "Note.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "SettingGamePlay.h"
#include<stdio.h>
#include "SDL_mixer.h"
Note::Note(float secStart, float secLength, Mix_Chunk* musicBGM)
{
	_sprite = NULL;
	_secStart = secStart;
	_lengthTick = (int)(secLength*1000.0f);
	if (0 == _lengthTick)
	{
		_eNoteStatus = NOMMAL_NOTE;
	}
	else
	{
		_eNoteStatus = LONG_NOTE;
	}
	_musicBGM = musicBGM;
}

Note::~Note()
{
}
void Note::Init()
{
	_updateDuration = SettingGamePlay::GetInstance()->GetGameTimeTick() - (int)(_secStart*1000.0f) - _lengthTick;
	_x = -1;
	_y = UpdatePositionY(_updateDuration);
	_isLive = true;
	_isJudge = false;

	_sprite = new Sprite(_spriteCSVName);
	_sprite->Init();
	_sprite->SetPosition(_x, _y);
	if (LONG_NOTE == _eNoteStatus)
	{
		float lengthRate = (float)_lengthTick / SettingGamePlay::GetInstance()->GetGameTimeTick();
		_length = lengthRate * SettingGamePlay::GetInstance()->GetTrackHeight();
		_sprite->SetHeight(_length);
		_sprite->SetPivotY(0.0f);
	}
}
void Note::Dinit()
{
	if (NULL != _sprite)
	{
		delete _sprite;
		_sprite = NULL;
	}
}
void Note::Update(int deltaTime)
{
	_updateDuration += deltaTime;
	if (false == IsNoteEndTick(_updateDuration))
	{
		_y = UpdatePositionY(_updateDuration);
		_sprite->SetPosition(_x, _y);
		_sprite->Update(deltaTime);
	}
	else
	{
		IsDead();
		_sprite->SetHeight(0);
	}
	if (LONG_NOTE == _eNoteStatus)
	{
		if (_isJudge)
		{
			_lengthTick -= deltaTime;
			float lengthRate = (float)_lengthTick / SettingGamePlay::GetInstance()->GetGameTimeTick();

			_length = lengthRate * SettingGamePlay::GetInstance()->GetTrackHeight();
			_sprite->SetHeight(_length);
		}
		if (true == IsNoteEndTick(_updateDuration + _lengthTick))
		{
			_lengthTick -= deltaTime;
			float lengthRate = (float)_lengthTick / SettingGamePlay::GetInstance()->GetGameTimeTick();

			_length = (GameSystem::GetInstance()->GetHeight() - 152) - UpdatePositionY(_updateDuration);
			_sprite->SetHeight(_length);
		}
	}
}
void Note::Render()
{
	_sprite->Render();
}
int Note::UpdatePositionY(int deltaDuration)
{
	int trackHeight = SettingGamePlay::GetInstance()->GetTrackHeight();
	float positionRate = (float)deltaDuration / (float)SettingGamePlay::GetInstance()->GetGameTimeTick();
	float positionInSec = trackHeight * positionRate;
	int yPos = (positionInSec - (trackHeight - GameSystem::GetInstance()->GetHeight() + SettingGamePlay::GetInstance()->GetCollisionDeltaLine()));
	if (yPos >= GameSystem::GetInstance()->GetHeight() - 152)
	{
		yPos = GameSystem::GetInstance()->GetHeight() - 152;
	}
	return yPos;
}
bool Note::IsNoteEndTick(int deltaDuration)
{
	if (deltaDuration < SettingGamePlay::GetInstance()->GetGameTimeTick() + 152)
		return false;
	return true;
}
void Note::AdjustmentHeight()
{
	_lengthTick = SettingGamePlay::GetInstance()->GetGameTimeTick() - _updateDuration;
	float lengthRate = (float)_lengthTick / SettingGamePlay::GetInstance()->GetGameTimeTick();
	_length = lengthRate * SettingGamePlay::GetInstance()->GetTrackHeight();
	_sprite->SetHeight(_length);
}
void Note::SetSpriteName(string spriteCSV)
{
	_spriteCSVName = spriteCSV;
	//sprintf(_spriteCSVName, "%s.csv", spriteCSV);
}
void Note::WavPlay()
{
	if (NULL != _musicBGM)
	{
		//printf("MP3 PLAY!\n");
		Mix_PlayChannel(-1, _musicBGM, 0);
	}
	else
	{
		printf("Note sound ERROR!!\n");
	}
}
bool Note::IsLive()
{
	return _isLive;
}
void  Note::IsDead()
{
	_isLive = false;
}
int Note::GetNoteTime()
{
	return _updateDuration;
}
eNoteStatus Note::GetNoteStatus()
{
	return _eNoteStatus;
}
int Note::GetlengthTick()
{
	return _lengthTick;
}
void Note::Judged()
{
	_isJudge = true;
}
bool Note::IsJudge()
{
	return _isJudge;
}
float Note::GetSecStart()
{
	return _secStart;
}
Mix_Chunk* Note::GetMusicBGM()
{
	return _musicBGM;
}
bool Note::IsKeyDownJudgeSuccess()
{
	//WavPlay();
	if (eNoteStatus::NOMMAL_NOTE == _eNoteStatus)
	{
		return true;
	}
	else if (eNoteStatus::LONG_NOTE == _eNoteStatus)
	{
		AdjustmentHeight();
		Judged();
		return false;
	}
}