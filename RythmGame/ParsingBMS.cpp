//#include"ParsingBMS.h"
//#include"Wav.h"
//#include"NommalNote.h"
//#include"TrackManager.h"
//#include"SettingGamePlay.h"
//#include"GameSystem.h"
//#include<stdio.h>
//#include<iostream>
//ParsingBMS::ParsingBMS()
//{
//	_wavList.clear();
//}
//
//ParsingBMS::~ParsingBMS()
//{
//}
//void ParsingBMS::Init()
//{
//	char filePathBMS[256];
//	sprintf(filePathBMS, "../Resources/BMS/[Cosine]_Happy_Driver/%s", "Happy_Driver_[7Normal].bms");
//	BMSFileRead(filePathBMS);
//
//	SettingHeaderData();
//	SettingMainData();
//}
//void ParsingBMS::Dinit()
//{
//	for (vector<Wav*>::iterator it = _wavList.begin(); it != _wavList.end(); it++)
//	{
//		if (NULL != (*it))
//		{
//			(*it)->Dinit();
//			delete (*it);
//			(*it) = NULL;
//		}
//	}
//}
//void ParsingBMS::BMSFileRead(char* filePathBMS)
//{
//	FILE* fbms = fopen(filePathBMS, "r");
//	if (NULL == fbms)
//	{
//		printf("File 안열림 에러\n");
//	}
//
//	bool dataCheck = false;
//	char buffer[1024];
//	char * record = fgets(buffer, sizeof(buffer), fbms);
//	while (true)
//	{
//		record = fgets(buffer, sizeof(buffer), fbms);
//		if (NULL == record)
//			break;
//		{
//			char* token = strtok(record, "#\n");
//			if (NULL != token)
//			{
//				if (dataCheck) //노트 정보 파싱
//				{
//					_mainDataInfoList.push_back((string)token);
//				}
//				else
//				{
//					_headerDataInfoList.push_back((string)token);
//				}
//				if (!strcmp(token, "*---------------------- MAIN DATA FIELD"))
//					dataCheck = true;
//			}
//		}
//	}
//	fclose(fbms);
//}
//void ParsingBMS::SettingHeaderData()
//{
//	for (vector<string>::iterator itHeader = _headerDataInfoList.begin(); itHeader != _headerDataInfoList.end(); itHeader++)
//	{
//		//cout << (*it).substr(0, 3) << endl;
//		if (!(*itHeader).substr(0, 3).compare("WAV"))
//		{
//			string wavFileInfo = (*itHeader).substr(3, 2);
//			string wavFileName = (*itHeader).substr(6, (*itHeader).length());
//			Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
//			char musicfilePath[256];
//			sprintf(musicfilePath, "../Resources/BMS/[Cosine]_Happy_Driver/%s", wavFileName.c_str());
//			Mix_Chunk* musicBGM = Mix_LoadWAV(musicfilePath);
//			_wavMap[wavFileInfo] = musicBGM;
//		}
//		else if (!(*itHeader).substr(0, 3).compare("BPM"))
//		{
//			int bpm = atoi((*itHeader).substr(4, 3).c_str());	//헤더
//			_measureStandardTimeSec = 60.0f * 4.0f / bpm;	//1마디 진행되는 초
//			{
//				//bms, gameTimeTick 세팅할 곳
//				vector<string>::iterator itMain = _mainDataInfoList.end();
//				itMain--;
//				_gamePlayTime = atoi((*itMain).substr(0, 3).c_str()) * _measureStandardTimeSec;
//			}
//			float trackHeight = GameSystem::GetInstance()->GetHeight()*_gamePlayTime;	//메인
//			SettingGamePlay::GetInstance()->SetGameTimeTick(_gamePlayTime);
//			SettingGamePlay::GetInstance()->SetTrackHeight(trackHeight);
//		}
//	}
//}
//void ParsingBMS::SettingMainData()
//{
//	for (vector<string>::iterator it = _mainDataInfoList.begin(); it != _mainDataInfoList.end(); it++)
//	{
//		string measureChannelInfo = (*it).substr(0, 5);
//		string placeNoteInfo = (*it).substr(6, (*it).length());
//		_measureNum = atoi(measureChannelInfo.substr(0, 3).c_str());
//		_channelNum = atoi(measureChannelInfo.substr(3, 2).c_str());
//		if (placeNoteInfo.compare("00"))
//		{
//			if (0 == atoi(measureChannelInfo.substr(3, 1).c_str()))
//			{
//				//autoWav
//				float measureSecSet = (float)_measureNum * _measureStandardTimeSec + SettingGamePlay::GetInstance()->GetGameLoadTime();
//				float bitSec = _measureStandardTimeSec / (placeNoteInfo.length() / 2);
//				for (int i = 0; placeNoteInfo.compare(""); i++)
//				{
//					if (placeNoteInfo.substr(0, 2).compare("00"))
//					{
//						Wav* wav = new Wav(measureSecSet, _wavMap[placeNoteInfo.substr(0, 2)]);
//						wav->Init();
//						_wavList.push_back(wav);
//					}
//					measureSecSet += bitSec;
//					placeNoteInfo = placeNoteInfo.substr(2, placeNoteInfo.length());
//				}
//			}
//			else
//			{
//				//note
//				_noteInfoMap[measureChannelInfo] = placeNoteInfo;
//			}
//		}
//	}
//}