#pragma once
#include<map>
using namespace std;
enum eKeyStatus
{
	DOWN,
	HOLD,
	UP,
	KEY_NONE,
};
enum eTrackNum;
class InputManager
{
private:
	static InputManager* _instance;
public:
	static InputManager* GetInstance();
private:
	InputManager();
public:
	~InputManager();
//public:
//	void Update(int deltaTime);
//	void Render();
//
private:
	map<int, eTrackNum> _trackKeyMap;
	map<eTrackNum, eKeyStatus> _trackKeyStatus;
public:
	void Init();
	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
	eKeyStatus GetKeyStatus(eTrackNum trackNum);
	bool IsKeyDown(eTrackNum trackNum);
	bool IsKeyHold(eTrackNum trackNum);
	bool IsKeyUp(eTrackNum trackNum);
};