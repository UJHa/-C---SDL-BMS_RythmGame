#pragma once
#include<map>
#include<list>
#include<vector>
#include "GameObject.h"
using namespace std;
class Note;
class Sprite;
class KeyboardEffectSprite;
class Font;
enum eTrackNum;
enum eJudge
{
	GREAT,
	GOOD,
	BAD,
	POOR,
	NONE,
};
class Track : public GameObject
{
private:
	//int _posX;
	list<Note *> _deleteNoteList;

	Sprite* _boomSprite;
	KeyboardEffectSprite* _keyboardEffectSprite;
	KeyboardEffectSprite* _trackEffectSprite;

	map<int, list<Note*>> _measureNoteList;
	eJudge _judge;

	//int _trackWidth;
	int _maxMeasureIndex;
	eTrackNum _trackInfo;
	string _noteSpriteName;

	int _updateDuration;
	int _updateIndex;
public:
	Track(eTrackNum trackInfo, string noteSpriteName);
	~Track();
	void Init();
	void Dinit();
	void Update(int deltaTime);
	void Render();
	//init 
private:
	int _judgeBadStartTick;
	int _judgeBadEndTick;
	int _judgeGoodStartTick;
	int _judgeGoodEndTick;
	int _judgePerfectStartTick;
	int _judgePerfectEndTick;
public:
	void SetJudgeTick();
	void SetNotePlace();
	eJudge ChangeJudgeText(int noteTime);
	//update list
public:
	void UpdateKeyEvent();
	void UpdateMeasureIndex(int deltaTime);
	void UpdateMeasureNoteList(int deltaTime);
};