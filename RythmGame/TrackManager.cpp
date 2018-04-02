#include "SDL.h"
#include"TrackManager.h"
#include"GameSystem.h"
#include"SettingGamePlay.h"
#include"Note.h"
#include<stdlib.h>
#include<iostream>
#include"Font.h"
#include"Wav.h"
#include"SDL_mixer.h"
TrackManager::TrackManager()
{
	_trackList.clear();
}
TrackManager::~TrackManager()
{
}
void TrackManager::Init()
{
	TrackListInit();
}
void TrackManager::Dinit()
{
	for (map<int, Track*>::iterator it = _trackList.begin(); it != _trackList.end(); it++)
	{
		(*it).second->Dinit();
	}
	_trackList.clear();
}
void TrackManager::Update(int deltaTime)
{
	for (map<int, Track*>::iterator it = _trackList.begin(); it != _trackList.end(); it++)
	{
		(*it).second->Update(deltaTime);
	}
}
void TrackManager::Render()
{
	for (map<int, Track*>::iterator it = _trackList.begin(); it != _trackList.end(); it++)
	{
		(*it).second->Render();
	}
}
void TrackManager::KeyDown(eTrackNum keyTrack)
{
	if(eTrackNum::TRACK_NONE !=keyTrack)
		_trackList[keyTrack]->KeyDown();
}
void TrackManager::KeyUp(eTrackNum keyTrack)
{
	if (eTrackNum::TRACK_NONE != keyTrack)
		_trackList[keyTrack]->KeyUp();
}
void TrackManager::TrackListInit()
{
	int posY = GameSystem::GetInstance()->GetHeight() / 2;

	Track* track1 = new Track(eTrackNum::SCRATCH, "noteScratch.csv");
	Track* track2 = new Track(eTrackNum::KEY1, "noteKey1.csv");
	Track* track3 = new Track(eTrackNum::KEY2, "noteKey2.csv");
	Track* track4 = new Track(eTrackNum::KEY3, "noteKey3.csv");
	Track* track5 = new Track(eTrackNum::KEY4, "noteKey4.csv");
	Track* track6 = new Track(eTrackNum::KEY5, "noteKey5.csv");
	Track* track7 = new Track(eTrackNum::KEY6, "noteKey6.csv");
	Track* track8 = new Track(eTrackNum::KEY7, "noteKey7.csv");

	_trackList[eTrackNum::SCRATCH] = track1;
	_trackList[eTrackNum::KEY1] = track2;
	_trackList[eTrackNum::KEY2] = track3;
	_trackList[eTrackNum::KEY3] = track4;
	_trackList[eTrackNum::KEY4] = track5;
	_trackList[eTrackNum::KEY5] = track6;
	_trackList[eTrackNum::KEY6] = track7;
	_trackList[eTrackNum::KEY7] = track8;


	for (map<int, Track*>::iterator it = _trackList.begin(); it != _trackList.end(); it++)
	{
		(*it).second->Init();
	}
}