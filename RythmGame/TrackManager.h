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
enum eTrackNum
{
	TRACK_NONE,
	KEY1,
	KEY2,
	KEY3,
	KEY4,
	KEY5,
	SCRATCH,
	KEY6 = 8,
	KEY7,
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
	void KeyDown(eTrackNum keyTrack);
	void KeyUp(eTrackNum keyTrack);
	//Init simplify functions
public:
	void TrackListInit();
};