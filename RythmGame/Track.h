#pragma once
#include<map>
#include<list>
#include<vector>
#include "GameObject.h"
using namespace std;
class Note;
class Sprite;
class Font;
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
	map<int, list<Note*>> _measureNoteList;
	eJudge _judge;

	//int _trackWidth;
	int _testMaxMeasureIndex;
	int _trackInfo;
	string _noteSpriteName;

	int _updateDuration;
	int _updateIndex;
public:
	Track(int trackInfo, string noteSpriteName);
	~Track();
	void Init();
	void Dinit();
	void Update(int deltaTime);
	void Render();
	//keySet
private:
	bool _isKeyDown;
public:
	void KeyDown();
	void KeyUp();
	void JudgeDownEvent();
	void JudgeUpEvent();

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
	void UpdateMeasureIndex(int deltaTime);
	void UpdateMeasureNoteList(int deltaTime);
	//set font
	void SetFont();
};