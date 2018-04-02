#include<stdio.h>
#include<SDL.h>
#include "InputManager.h"
#include "TrackManager.h"
InputManager* InputManager::_instance = NULL;
InputManager* InputManager::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new InputManager();
		_instance->Init();
	}
	return _instance;
}
InputManager::InputManager()
{

}
InputManager::~InputManager()
{
}
void InputManager::Init()
{
	_trackKeyMap.clear();
	_trackKeyMap[SDLK_a] = eTrackNum::SCRATCH;
	_trackKeyMap[SDLK_s] = eTrackNum::KEY1;
	_trackKeyMap[SDLK_d] = eTrackNum::KEY2;
	_trackKeyMap[SDLK_f] = eTrackNum::KEY3;
	_trackKeyMap[SDLK_g] = eTrackNum::KEY4;
	_trackKeyMap[SDLK_h] = eTrackNum::KEY5;
	_trackKeyMap[SDLK_j] = eTrackNum::KEY6;
	_trackKeyMap[SDLK_k] = eTrackNum::KEY7;

	for (int i = 0; i < eTrackNum::KEY7 + 1; i++)
	{
		_trackKeyStatus[(eTrackNum)i] = eKeyStatus::KEY_NONE;
	}
}
void InputManager::KeyDown(int keyCode)
{
	eTrackNum trackNum = _trackKeyMap[keyCode];
	if (eTrackNum::TRACK_NONE != trackNum)
		_trackKeyStatus[trackNum] = eKeyStatus::DOWN;
}
void InputManager::KeyUp(int keyCode)
{
	eTrackNum trackNum = _trackKeyMap[keyCode];
	if (eTrackNum::TRACK_NONE != trackNum)
		_trackKeyStatus[trackNum] = eKeyStatus::UP;
}
eKeyStatus InputManager::GetKeyStatus(eTrackNum trackNum)
{
	return _trackKeyStatus[trackNum];
}
bool InputManager::IsKeyDown(eTrackNum trackNum)
{
	if (eKeyStatus::DOWN == _trackKeyStatus[trackNum])
	{
		_trackKeyStatus[trackNum] = eKeyStatus::HOLD;
		return true;
	}
	return false;
}
bool InputManager::IsKeyHold(eTrackNum trackNum)
{
	if (eKeyStatus::HOLD == _trackKeyStatus[trackNum])
	{
		return true;
	}
	return false;
}
bool InputManager::IsKeyUp(eTrackNum trackNum)
{
	if (eKeyStatus::UP == _trackKeyStatus[trackNum])
	{
		_trackKeyStatus[trackNum] = eKeyStatus::KEY_NONE;
		return true;
	}
	return false;
}