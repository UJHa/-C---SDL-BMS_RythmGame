#include<stdio.h>
#include<string.h>
#include "Track.h"
#include "Note.h"
#include "SettingGamePlay.h"
#include "Sprite.h"
#include "InputManager.h"
#include "KeyboardEffectSprite.h"
Track::Track(eTrackNum trackInfo, string noteSpriteName)
{
	_deleteNoteList.clear();
	_boomSprite = NULL;
	_keyboardEffectSprite = NULL;
	_trackEffectSprite = NULL;

	_measureNoteList.clear();
	_trackInfo = trackInfo;
	_judge = eJudge::NONE;
	_updateDuration = 0;
	_updateIndex = 0;
	_noteSpriteName = noteSpriteName;
}

Track::~Track() 
{
}
void Track::Init()
{
	SetJudgeTick(); 
	SetNotePlace();
	
	char boomSpriteName[256];
	sprintf(boomSpriteName, "noteBoomspr%d.csv", _trackInfo);
	_boomSprite = new Sprite(boomSpriteName);
	_boomSprite->Init();
	 
	char keyboardSpriteName[256];
	sprintf(keyboardSpriteName, "keyboardspr%d.csv", _trackInfo);
	_keyboardEffectSprite = new KeyboardEffectSprite(keyboardSpriteName);
	 _keyboardEffectSprite->Init();

	char trackEffectSpriteName[256];
	sprintf(trackEffectSpriteName, "trackEffectspr%d.csv", _trackInfo);
	_trackEffectSprite = new KeyboardEffectSprite(trackEffectSpriteName);
	_trackEffectSprite->Init();
}
void Track::Dinit()
{
	for (list<Note*>::iterator itr = _deleteNoteList.begin();
		itr != _deleteNoteList.end();
		itr++)
	{
		(*itr)->Dinit();
		delete (*itr);
	}
	_deleteNoteList.clear();

	if (NULL != _boomSprite)
	{
		delete _boomSprite;
		_boomSprite = NULL;
	}
	if (NULL != _keyboardEffectSprite)
	{
		delete _keyboardEffectSprite;
		_keyboardEffectSprite = NULL;
	}
	if (NULL != _trackEffectSprite)
	{
		delete _trackEffectSprite;
		_trackEffectSprite = NULL;
	}
}
void Track::Update(int deltaTime)
{
	UpdateKeyEvent();
	UpdateMeasureIndex(deltaTime);
	UpdateMeasureNoteList(deltaTime);
	_keyboardEffectSprite->Update(deltaTime);
	_trackEffectSprite->Update(deltaTime);
	_boomSprite->Update(deltaTime);
}
void Track::Render()
{
	_keyboardEffectSprite->Render();
	_trackEffectSprite->Render();
	_boomSprite->Render();
	for (int i = 1; i < 3 + _updateIndex; i++)
	{
		for (list<Note*>::iterator itr = _measureNoteList[i].begin();
			itr != _measureNoteList[i].end();
			itr++)
		{
			(*itr)->Render();
		}
	}
}
void Track::SetJudgeTick()
{
	_judgeBadStartTick = SettingGamePlay::GetInstance()->GetGameTimeTick()
		- 150;//(SettingGamePlay::GetInstance()->GetCollisionDeltaLine() - 25);
	_judgeBadEndTick = SettingGamePlay::GetInstance()->GetGameTimeTick()
		+ 150;//(SettingGamePlay::GetInstance()->GetCollisionDeltaLine() - 25);
	_judgeGoodStartTick = SettingGamePlay::GetInstance()->GetGameTimeTick()
		- 100;//(SettingGamePlay::GetInstance()->GetCollisionDeltaLine() - 50);
	_judgeGoodEndTick = SettingGamePlay::GetInstance()->GetGameTimeTick()
		+ 100;//(SettingGamePlay::GetInstance()->GetCollisionDeltaLine() - 50);
	_judgePerfectStartTick = SettingGamePlay::GetInstance()->GetGameTimeTick()
		- 50;// (SettingGamePlay::GetInstance()->GetCollisionDeltaLine() - 75);
	_judgePerfectEndTick = SettingGamePlay::GetInstance()->GetGameTimeTick()
		+ 50;//(SettingGamePlay::GetInstance()->GetCollisionDeltaLine() - 75);
}
void Track::SetNotePlace()
{
	vector<string> noteInfoList = SettingGamePlay::GetInstance()->GetNoteInfoMap()[_trackInfo];
	map<string, Mix_Chunk*> wavMap = SettingGamePlay::GetInstance()->GetWavMap();
	for (vector<string>::iterator it = noteInfoList.begin(); it != noteInfoList.end(); it++)
	{
		int measureNum = atoi((*it).substr(0, 3).c_str());	//마디 인덱스
		int loadingMeasureNum = measureNum;
		if (1 < loadingMeasureNum)
			loadingMeasureNum = 2;
		string placeNoteInfo = (*it).substr(6,(*it).length());		//마디 내 노트 정보
		float measureStandardTime = SettingGamePlay::GetInstance()->GetMeasureStandardTimeSec();	//마디 기준 시간
		float measureSecSet = (float)loadingMeasureNum * measureStandardTime + SettingGamePlay::GetInstance()->GetGameLoadTime();
		float bitSec = measureStandardTime / (float)(placeNoteInfo.length() / 2);

		while (placeNoteInfo.compare(""))	//노트 정보 한라인 읽기
		{
			if (placeNoteInfo.substr(0, 2).compare("00"))
			{
				Note* note;
				if (!placeNoteInfo.substr(0, 2).compare(SettingGamePlay::GetInstance()->GetLongNoteBit().c_str()))	//롱 노트 시 처리
				{
					list<Note*>::iterator itrLastNote = _measureNoteList[measureNum].end();
					if (0 == _measureNoteList[measureNum].size())
						itrLastNote = _measureNoteList[measureNum - 1].end();
					itrLastNote--;
					
					float prevSecSet = (*itrLastNote)->GetSecStart();
					float noteLength = measureSecSet - prevSecSet;
					if (noteLength < 0)
						noteLength = - noteLength;
					note = new Note(prevSecSet, noteLength, (*itrLastNote)->GetMusicBGM());
					_measureNoteList[measureNum].remove(*itrLastNote);

					char longNoteSpriteCSVName[256];
					sprintf(longNoteSpriteCSVName, "long%s", _noteSpriteName.c_str());
					note->SetSpriteName(longNoteSpriteCSVName);
				}
				else
				{
					note = new Note(measureSecSet, 0, wavMap[placeNoteInfo.substr(0, 2)]);
					note->SetSpriteName(_noteSpriteName);
				}
				note->Init();
				_measureNoteList[measureNum].push_back(note);
				_maxMeasureIndex = measureNum;
			}
			measureSecSet += bitSec;
			placeNoteInfo = placeNoteInfo.substr(2, placeNoteInfo.length());
		}
	}
}
eJudge Track::ChangeJudgeText(int noteTime)
{
	if (_judgePerfectStartTick <= noteTime && noteTime <= _judgePerfectEndTick)
	{
		return eJudge::GREAT;
	}
	else if (_judgeGoodStartTick <= noteTime && noteTime <= _judgeGoodEndTick)
	{
		return eJudge::GOOD;
	}
	else if (_judgeBadStartTick <= noteTime && noteTime <= _judgeBadEndTick)
	{
		return eJudge::BAD;
	}
	else if( noteTime < _judgeBadStartTick )	//여기 조건 계산하기
	{
		return eJudge::NONE;
	}
	else
	{
		return eJudge::POOR;
	}
}
void Track::UpdateKeyEvent()
{
	int startMeasureIndex = 0;
	while (0 == _measureNoteList[startMeasureIndex].size())
	{
		startMeasureIndex++;
		if (_maxMeasureIndex < startMeasureIndex)
			break;
	}
	list<Note*>::iterator itr = _measureNoteList[startMeasureIndex].begin();

	if (InputManager::GetInstance()->IsKeyDown(_trackInfo))//eKeyStatus::DOWN == InputManager::GetInstance()->GetKeyStatus(_trackInfo))
	{
		if (itr == _measureNoteList[startMeasureIndex].end())	//null 체크
			return;
		printf("%d down\n",_trackInfo);
		_keyboardEffectSprite->Play();
		_trackEffectSprite->Play();

		int noteTime = (*itr)->GetNoteTime() + (*itr)->GetlengthTick();
		_judge = ChangeJudgeText(noteTime);

		if (eJudge::NONE == _judge)
			return;

		SettingGamePlay::GetInstance()->GetJudgeFont(_judge)->Play();
		SettingGamePlay::GetInstance()->AddJudgeCount(_judge);
		
		bool isRemoveCheck = true;
		switch (_judge)
		{
		case eJudge::GREAT:
		case eJudge::GOOD:
			SettingGamePlay::GetInstance()->AddCombo();
			_boomSprite->Play();
			(*itr)->WavPlay();
			isRemoveCheck = (*itr)->IsKeyDownJudgeSuccess();
			break;
		case eJudge::BAD:
		case eJudge::POOR:
			SettingGamePlay::GetInstance()->ResetCombo();
			isRemoveCheck = true;
			break;
		}
		if (isRemoveCheck)
		{
			_deleteNoteList.push_back(*itr);
			_measureNoteList[startMeasureIndex].remove(*itr);
		}
	}
	else if (InputManager::GetInstance()->IsKeyHold(_trackInfo))//eKeyStatus::HOLD == InputManager::GetInstance()->GetKeyStatus(_trackInfo))
	{
		if (itr == _measureNoteList[startMeasureIndex].end())	//null 체크
			return;
		printf("%d hold\n", _trackInfo);
		if ((*itr)->IsJudge())	//롱노트 status일때 코드
		{
			_judge = eJudge::GREAT;
			SettingGamePlay::GetInstance()->GetJudgeFont(_judge)->Play();
			SettingGamePlay::GetInstance()->AddJudgeCount(_judge);
			
			SettingGamePlay::GetInstance()->AddCombo();
			_boomSprite->Play();
			(*itr)->AdjustmentHeight();
		}
		else
		{
			_judge = eJudge::NONE;
		}
	}
	else if (InputManager::GetInstance()->IsKeyUp(_trackInfo))//eKeyStatus::UP == InputManager::GetInstance()->GetKeyStatus(_trackInfo))
	{
		printf("%d up\n", _trackInfo);
		_keyboardEffectSprite->Stop();
		_trackEffectSprite->Stop();

		if (itr == _measureNoteList[startMeasureIndex].end())	//null 체크
			return;
		int noteTime = (*itr)->GetNoteTime();
		if ((*itr)->IsJudge())
		{
			_judge = ChangeJudgeText(noteTime);

			if (eJudge::NONE != _judge)
			{
				SettingGamePlay::GetInstance()->GetJudgeFont(_judge)->Play();
				SettingGamePlay::GetInstance()->AddJudgeCount(_judge);
			}
			switch (_judge)
			{
			case eJudge::GREAT:
			case eJudge::GOOD:
				SettingGamePlay::GetInstance()->AddCombo();
				_boomSprite->Play();
				break;
			case eJudge::BAD:
			case eJudge::POOR:
				SettingGamePlay::GetInstance()->ResetCombo();
				break;
			}
			_deleteNoteList.push_back(*itr);
			_measureNoteList[startMeasureIndex].remove(*itr);
		}
	}
	else
	{
		if (itr == _measureNoteList[startMeasureIndex].end())	//null 체크
			return;
		if (_judgeBadEndTick <= (*itr)->GetNoteTime())
		{
			_judge = eJudge::POOR;
			SettingGamePlay::GetInstance()->GetJudgeFont(_judge)->Play();
			SettingGamePlay::GetInstance()->AddJudgeCount(_judge);

			SettingGamePlay::GetInstance()->ResetCombo();

			_deleteNoteList.push_back(*itr);
			_measureNoteList[startMeasureIndex].remove(*itr);
		}
	}
}
void Track::UpdateMeasureIndex(int deltaTime)
{
	_updateDuration += deltaTime;

	float measureStandardTime = SettingGamePlay::GetInstance()->GetMeasureStandardTimeSec();	//마디 기준 시간
	float measureSecSet = measureStandardTime;
	int measureMillisecSet = (int)(measureSecSet * 1000.0f);
	if (measureMillisecSet <= _updateDuration)
	{
		_updateIndex++;
		for (list<Note*>::iterator itr = _measureNoteList[3 + _updateIndex].begin();
			itr != _measureNoteList[3 + _updateIndex].end();
			itr++)
		{
			(*itr)->Update(_updateDuration - measureMillisecSet);
		}
		_updateDuration = _updateDuration - measureMillisecSet;
	}
}
void Track::UpdateMeasureNoteList(int deltaTime)
{
	for (int i = 1; i < 3 + _updateIndex; i++)
	{
		for (list<Note*>::iterator itr = _measureNoteList[i].begin();
			itr != _measureNoteList[i].end();
			itr++)
		{
			if ((*itr)->IsLive())
			{
				(*itr)->Update(deltaTime);
			}
		}
	}
}