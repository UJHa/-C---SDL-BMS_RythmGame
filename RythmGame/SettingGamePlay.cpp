#include <stdio.h>
#include <io.h>
#include "SettingGamePlay.h"
#include "GameSystem.h"
#include<SDL.h>
#include "Font.h"
#include "Wav.h"
#include "time.h"
SettingGamePlay* SettingGamePlay::_instance = NULL;
SettingGamePlay* SettingGamePlay::GetInstance()
{
	if (_instance == NULL)
		_instance = new SettingGamePlay();
	return _instance;
}
SettingGamePlay::SettingGamePlay()
{
	_comboNum = 0;
	_maxComboNum = 0;
	_bmsFile = NULL;
	_judgeCountList.resize(4);
}
SettingGamePlay::~SettingGamePlay()
{
}
void SettingGamePlay::ResetData()
{
	_bmsInfo.clear();
	_noteInfoMap.clear();
	_wavChunkMap.clear();
	_longNoteBit = "";
	ResetCombo();
	_maxComboNum = 0;
	_bmsFile = GetFilePointerBMS();
	_itBms = _bmsInfo.end();	//null 세팅
	_isFileReadFinish = false;
	for (int i = 0; i < _judgeCountList.size(); i++)
	{
		_judgeCountList[i] = 0;
	}

}
void SettingGamePlay::ResetData(string fileRoute, string fileBMS)
{
	_fileRoute = fileRoute;
	_BMSname = fileBMS;
	ResetData();
}
void SettingGamePlay::Dinit()
{
	_bmsInfo.clear();
	_noteInfoMap.clear();
	_wavChunkMap.clear();
	_wavSecMap.clear();

	_judgeFontSpriteList.clear();
	for (vector<Wav*>::iterator it = _autoWavList.begin(); it != _autoWavList.end(); it++)
	{
		if (NULL != (*it))
		{
			(*it)->Dinit();
			delete (*it);
			(*it) = NULL;
		}
	}
	_autoWavList.clear();
}
FILE* SettingGamePlay::GetFilePointerBMS()
{
	FILE* bmsFile;
	char filePathBMS[256];
	sprintf(filePathBMS, (_fileRoute + "/" + _BMSname).c_str());
	printf("fileRoute Check : %s\n", filePathBMS);
	bmsFile = fopen(filePathBMS, "r");
	if (NULL == bmsFile)
	{
		printf("File 안열림 에러\n");
	}
	return bmsFile;
}
void SettingGamePlay::AddCombo()
{
	_comboNum++;
	_numberSprite->SetNumber(_comboNum);
	if (_comboNum > _maxComboNum)
	{
		_maxComboNum = _comboNum;
	}
}
int SettingGamePlay::GetCollisionDeltaLine()
{
	int trackEndLength = GameSystem::GetInstance()->GetHeight() / 2 - 248;	//152
	return trackEndLength + 100;
}
bool SettingGamePlay::SettingData(int deltaTime)
{
	//이제 반복문을 n번씩 update에서 실행하도록 변경
	if (true == BMSFileRead(deltaTime))
	{
		if (true == ParsingBMS(deltaTime))
		{
			for (map<float, vector<Mix_Chunk*>>::iterator it = _wavSecMap.begin();
				it != _wavSecMap.end(); it++)
			{
				float wavSec = (*it).first;
				vector<Mix_Chunk*> wavBGMList = (*it).second;
				Wav* wav = new Wav(wavSec, wavBGMList);
				wav->Init();
				_autoWavList.push_back(wav);
			}
			return true;
		}
	}
	return false;
}
bool SettingGamePlay::BMSFileRead(int deltaTime)
{
	if (true == _isFileReadFinish)
		return true;

	int startTick = SDL_GetTicks();
	char buffer[1024];
	while (true)
	{
		char* record = fgets(buffer, sizeof(buffer), _bmsFile);
		if (NULL == record)
		{
			fclose(_bmsFile);
			printf("BMSFileRead 다 읽었어양!\n");
			_itBms = _bmsInfo.begin();
			_isFileReadFinish = true;
			return true;
		}
		{
			char* token = strtok(record, "\n");
			if (NULL != token)
			{
				string line = token;
				if (!line.substr(0, 1).compare("#"))
				{
					_bmsInfo.push_back(line.substr(1, line.length()));
				}
			}
		}
		int oneTimeDelta = SDL_GetTicks() - startTick;
		if (deltaTime <= oneTimeDelta)	//16이 델타값
		{
			printf("BMSFileRead 아직 읽는중에양\n");
			return false;
		}
	}
}
bool SettingGamePlay::ParsingBMS(int deltaTime)
{
	int startTick = SDL_GetTicks();
	while (true)
	{
		if (!(*_itBms).substr(0, 3).compare("WAV"))
		{
			string wavFileInfo = (*_itBms).substr(3, 2);
			string wavFileName = (*_itBms).substr(6, (*_itBms).length());
			Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
			Mix_AllocateChannels(256);
			char musicfilePath[256];
			sprintf(musicfilePath, (_fileRoute + "/%s").c_str(), wavFileName.c_str());
			Mix_Chunk* musicBGM = Mix_LoadWAV(musicfilePath);
			if (NULL == musicBGM)
			{ 
				//사운드 파일 없을 시
				printf("%s\n", wavFileName.c_str());
			}
			_wavChunkMap[wavFileInfo] = musicBGM;
		}
		else if (!(*_itBms).substr(0, 3).compare("BPM"))
		{
			int bpm = atoi((*_itBms).substr(4, 3).c_str());
			float bitPerSecond = 60.0f / (bpm* 8.0f);
			_measureStandardTimeSec = bitPerSecond * 32.0f;	//1마디 진행되는 초
			{
				//bms, gameTimeTick 세팅할 곳
				_gamePlayTime = atoi(_bmsInfo[_bmsInfo.size() - 1].substr(0, 3).c_str()) * _measureStandardTimeSec;
			}
			float trackHeight = GameSystem::GetInstance()->GetHeight()*_gamePlayTime * 1.0f;	//메인 * noteSpeed
			SetGameTimeTick(_gamePlayTime);
			SetTrackHeight(trackHeight);
		}
		else if (!(*_itBms).substr(0, 5).compare("LNOBJ"))
		{
			_longNoteBit = (*_itBms).substr(6, 2).c_str();
		}
		else if (0 != atoi((*_itBms).substr(0, 5).c_str()))
		{
			string measureChannelInfo = (*_itBms).substr(0, 5);
			string placeNoteInfo = (*_itBms).substr(6, (*_itBms).length());
			_measureNum = atoi(measureChannelInfo.substr(0, 3).c_str());
			_channelNum = atoi(measureChannelInfo.substr(3, 2).c_str());
			if (placeNoteInfo.compare("00"))
			{
				if (1 == atoi(measureChannelInfo.substr(3, 2).c_str()))
				{
					//autoWav
					float measureSecSet = (float)_measureNum * _measureStandardTimeSec + GetGameLoadTime();
					float bitSec = _measureStandardTimeSec / (placeNoteInfo.length() / 2);
					for (int i = 0; placeNoteInfo.compare(""); i++)
					{
						if (placeNoteInfo.substr(0, 2).compare("00"))
						{
							_wavSecMap[measureSecSet].push_back(_wavChunkMap[placeNoteInfo.substr(0, 2)]);
						}
						measureSecSet += bitSec;
						placeNoteInfo = placeNoteInfo.substr(2, placeNoteInfo.length());
					}
				}
				else if (3 == atoi(measureChannelInfo.substr(3, 2).c_str()))
				{

				}
				else if (4 != atoi(measureChannelInfo.substr(3, 2).c_str()))
				{
					//note
					_noteInfoMap[atoi(measureChannelInfo.substr(4, 1).c_str())].push_back(*_itBms);
				}
			}
		}
		_itBms++;
		if (_itBms == _bmsInfo.end())
		{
			printf("ParsingBMS 다 읽었어양!\n");
			_isFileReadFinish = false;
			return true;
		}
		int oneTimeDelta = SDL_GetTicks() - startTick;
		if (deltaTime - 3 <= oneTimeDelta)	//델타값 : 한번의 업데이트 시간
		{
			printf("ParsingBMS 아직 읽는중\n");
			return false;
		}
	}
}
void SettingGamePlay::AddJudgeCount(int judge)
{
	_judgeCountList[judge]++;
}
int SettingGamePlay::GetJudgeCount(int judge)
{
	return _judgeCountList[judge];
}