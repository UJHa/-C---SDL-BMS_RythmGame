#include<SDL.h>
#include<SDL_mixer.h>
#include"Wav.h"
#include "SettingGamePlay.h"
Wav::Wav(float measureSec, vector<Mix_Chunk*> musicBGM)
{
	_updateDuration = SettingGamePlay::GetInstance()->GetGameTimeTick() - (int)(measureSec*1000.0f);	//note sec 세팅하듯 변경
	_isPlay = false;
	_musicBGMList = musicBGM;
}

Wav::~Wav()
{
	
}
void Wav::Init()
{
	
}
void Wav::Dinit()
{
	_isPlay = true;
	Mix_PauseMusic();
}
void Wav::Update(int deltaTime)
{
	if (_isPlay)
		return;
	_updateDuration += deltaTime;
	if (_updateDuration > SettingGamePlay::GetInstance()->GetGameTimeTick())
	{
		for (vector<Mix_Chunk*>::iterator it = _musicBGMList.begin();
			it != _musicBGMList.end(); it++)
		{
			Mix_Chunk* musicBGM = (*it);
			if (MIX_INIT_MP3 == Mix_Init(MIX_INIT_MP3))
			{
				if (NULL != musicBGM)
				{
					Mix_PlayChannel(-1, musicBGM, 0);
					_isPlay = true;
				}
				else
				{
					printf("Auto sound LOAD ERROR!!\n");
				}
			}
		}
	}
}