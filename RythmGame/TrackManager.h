#pragma once
#include<vector>
#include<map>
#include<string>
#include "Track.h"
using namespace std;
class Font;
class Wav;
struct Mix_Chunk;
//key
//enum eTrackNum
//{
//	SCRATCH,
//	KEY1,
//	KEY2,
//	KEY3,
//	KEY4,
//	KEY5,
//	KEY6,
//	KEY7,
//	NONE,
//};
enum eTrackNum
{
	KEY1 = 1,
	KEY2,
	KEY3,
	KEY4,
	KEY5,
	SCRATCH,
	KEY6 = 8,
	KEY7,
	TRACK_NONE,
};
class TrackManager
{
private:
	map<int, Track*> _trackList;
public:
	TrackManager();
	~TrackManager();

	void Init();
	void Dinit();
	void Update(int deltaTime);
	void Render();
public:
	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
	//Init simplify functions
public:
	void TrackListInit();
};