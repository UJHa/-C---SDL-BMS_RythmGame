#pragma once
#include<vector>
#include<map>
#include<string>
#include "Track.h"
using namespace std;
//key
enum eTrackNum
{
	TRACK_NONE,
	KEY1,
	KEY2,
	KEY3,
	KEY4,
	KEY5,
	SCRATCH,
	NOT_USE,
	KEY6,
	KEY7,
};
class TrackManager
{
private:
	map<int, Track*> _trackList;
	Sprite* _collisionSprite;
public:
	TrackManager();
	~TrackManager();

	void Init();
	void Dinit();
	void Update(int deltaTime);
	void Render();
	//Init simplify functions
public:
	void TrackListInit();
};