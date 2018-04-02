#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Track.h"
#include "Note.h"
#include "SettingGamePlay.h"
#include "GameSystem.h"
#include "Sprite.h"
#include "Font.h"
#include "InputManager.h"
Track::Track(eTrackNum trackInfo, string noteSpriteName)
{
	_measureNoteList.clear();
	_trackInfo = trackInfo;
	_judge = NONE;
	_updateDuration = 0;
	_updateIndex = 0;
	_noteSpriteName = noteSpriteName;
}

Track::~Track()
{
}
void Track::Init()
{
	_isKeyDown = false;
	SetJudgeTick();
	SetNotePlace();
	
	char boomSpriteName[256];
	sprintf(boomSpriteName, "noteBoomspr%d.csv", _trackInfo);
	_boomSprite = new Sprite(boomSpriteName);
	_boomSprite->Init();
}
void Track::Dinit()
{
	{
		for (list<Note*>::iterator itr = _deleteNoteList.begin();
			itr != _deleteNoteList.end();
			itr++)
		{
			(*itr)->Dinit();
			delete (*itr);
		}
		_deleteNoteList.clear();
	}
}
void Track::Update(int deltaTime)
{
	UpdateKeyEvent();
	UpdateMeasureIndex(deltaTime);
	UpdateMeasureNoteList(deltaTime);
	_boomSprite->Update(deltaTime);
}
void Track::Render()
{
	for (int i = 1; i < 3 + _updateIndex; i++)
	{
		for (list<Note*>::iterator itr = _measureNoteList[i].begin();
			itr != _measureNoteList[i].end();
			itr++)
		{
			(*itr)->Render();
		}
	}
	_boomSprite->Render();
}
void Track::KeyDown()
{
	if (_isKeyDown)
		return;
	_isKeyDown = true;

	int index = 0;
	while (0 == _measureNoteList[index].size())
	{
		index++;
		if (_testMaxMeasureIndex < index)
			break;
	}
	list<Note*>::iterator itr = _measureNoteList[index].begin();
	if (itr == _measureNoteList[index].end())	//null 체크
		return;
	int noteTime = (*itr)->GetNoteTime() + (*itr)->GetlengthTick();

	if (noteTime < _judgeBadStartTick)
	{
		_judge = eJudge::NONE;
	}
	else
	{
		JudgeDownEvent();
	}
}
void Track::KeyUp()
{
	int index = 0;
	while (0 == _measureNoteList[index].size())
	{
		index++;
		if (_testMaxMeasureIndex < index)
			break;
	}
	list<Note*>::iterator itr = _measureNoteList[index].begin();
	if (itr == _measureNoteList[index].end())	//null 체크
		return;
	if ((*itr)->GetNoteStatus() == eNoteStatus::NOMMAL_NOTE)
	{
	}
	else if ((*itr)->GetNoteStatus() == eNoteStatus::LONG_NOTE)
	{
		if ((*itr)->IsJudge())
		{
			JudgeUpEvent();
		}
	}
	_isKeyDown = false;
}
void Track::JudgeDownEvent()
{
	int index = 0;
	while (0 == _measureNoteList[index].size())
	{
		index++;
		if (_testMaxMeasureIndex < index)
			break;
	}
	list<Note*>::iterator itr = _measureNoteList[index].begin();
	int noteTime = (*itr)->GetNoteTime() + (*itr)->GetlengthTick();
	_judge = ChangeJudgeText(noteTime);

	if (_judge < eJudge::NONE)
	{
		SettingGamePlay::GetInstance()->GetJudgeFont(_judge)->Play();
		SettingGamePlay::GetInstance()->AddJudgeCount(_judge);
	}
	if ((*itr)->GetNoteStatus() == eNoteStatus::NOMMAL_NOTE)
	{
		switch (_judge)
		{
		case eJudge::GREAT:
		case eJudge::GOOD:
			SettingGamePlay::GetInstance()->AddCombo();
			_boomSprite->Play();
			(*itr)->WavPlay();
			_measureNoteList[index].remove(*itr);
			break;
		case eJudge::BAD:
		case eJudge::POOR:
			SettingGamePlay::GetInstance()->ResetCombo();
			_measureNoteList[index].remove(*itr);
			break;
		case eJudge::NONE:
			break;
		}
	}
	else if ((*itr)->GetNoteStatus() == eNoteStatus::LONG_NOTE)
	{
		if ((*itr)->IsJudge())	//롱노트 status일때 코드
		{
			_judge = eJudge::GREAT;
		}
		switch (_judge)
		{
		case eJudge::GREAT:
		case eJudge::GOOD:
			SettingGamePlay::GetInstance()->AddCombo();
			_boomSprite->Play();
			(*itr)->AdjustmentHeight();
			(*itr)->Judged();
			_isKeyDown = false;
			break;
		case eJudge::BAD:
		case eJudge::POOR:
			SettingGamePlay::GetInstance()->ResetCombo();
			_measureNoteList[index].remove(*itr);
			_isKeyDown = true;
			break;
		case eJudge::NONE:
			_isKeyDown = true;
			break;
		}
	}
	SetFont();
}
void Track::JudgeUpEvent()
{
	int index = 0;
	while (0 == _measureNoteList[index].size())
	{
		index++;
		if (_testMaxMeasureIndex < index)
			break;
	}
	list<Note*>::iterator itr = _measureNoteList[index].begin();
	int noteTime = (*itr)->GetNoteTime();
	_judge = ChangeJudgeText(noteTime);

	if (_judge < eJudge::NONE)
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
		_measureNoteList[index].remove(*itr);
		break;
	case eJudge::BAD:
	case eJudge::POOR:
		SettingGamePlay::GetInstance()->ResetCombo();
		_measureNoteList[index].remove(*itr);
		break;
	case eJudge::NONE:
		break;
	}
	SetFont();
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
						noteLength = -noteLength;
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
				_testMaxMeasureIndex = measureNum;
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
	else
	{
		return eJudge::POOR;
	}
}
void Track::UpdateKeyEvent()
{
	if (InputManager::GetInstance()->IsKeyDown(_trackInfo))//eKeyStatus::DOWN == InputManager::GetInstance()->GetKeyStatus(_trackInfo))
	{
		printf("%d key Down!\n", _trackInfo);
	}
	else if (InputManager::GetInstance()->IsKeyHold(_trackInfo))//eKeyStatus::HOLD == InputManager::GetInstance()->GetKeyStatus(_trackInfo))
	{
		printf("%d key Hold!\n", _trackInfo);
	}
	else if (InputManager::GetInstance()->IsKeyUp(_trackInfo))//eKeyStatus::UP == InputManager::GetInstance()->GetKeyStatus(_trackInfo))
	{
		printf("%d key Up!\n", _trackInfo);
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
		list<Note*> eraseNoteList;
		for (list<Note*>::iterator itr = _measureNoteList[i].begin();
			itr != _measureNoteList[i].end();
			itr++)
		{
			if ((*itr)->IsLive())
			{
				(*itr)->Update(deltaTime);
			}
			if (_judgeBadEndTick <= (*itr)->GetNoteTime())
			{
				eraseNoteList.push_back(*itr);
				SettingGamePlay::GetInstance()->ResetCombo();

				_judge = eJudge::POOR;
				SettingGamePlay::GetInstance()->GetJudgeFont(_judge)->Play();
				SettingGamePlay::GetInstance()->AddJudgeCount(_judge);

				SetFont();
			}
		}
		if (0 != eraseNoteList.size())
		{
			list<Note*>::iterator itr = eraseNoteList.begin();
			while (itr != eraseNoteList.end())
			{
				_deleteNoteList.push_back(*itr);
				_measureNoteList[i].remove(*itr);
				itr++;
			}
		}
	}
}
void Track::SetFont()
{
	char text[256];
	sprintf(text, "Combo %04d Score 0000", SettingGamePlay::GetInstance()->GetComboNum());
	SettingGamePlay::GetInstance()->GetFontList()[0]->SetText(text, 255, 255, 255);

	_judge = NONE;
}