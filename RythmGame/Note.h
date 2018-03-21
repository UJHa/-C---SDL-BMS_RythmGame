#pragma once
#include "GameObject.h"
#include <string>
using namespace std;
class Sprite;
class Texture;
struct Mix_Chunk;
enum eNoteStatus
{
	NOMMAL_NOTE,
	LONG_NOTE,
};
class Note : public GameObject
{
protected:
	Sprite* _sprite;
	eNoteStatus _eNoteStatus;
	int _lengthTick;
	int _updateDuration;
	Mix_Chunk* _musicBGM;
	bool _isLive;
	bool _isJudge;
	int _x;
	int _y;

	float _secStart;

	string _spriteCSVName;
	int _length;
public:
	Note(float secStart, float secLength, Mix_Chunk* musicBGM);
	~Note();
	void Init();
	void Dinit();
	void Update(int deltaTime);
	void Render();
	int UpdatePositionY(int deltaDuration);
	bool IsNoteEndTick(int deltaDuration);

	void AdjustmentHeight();
	void SetSpriteName(string spriteCSV);
	void WavPlay();
	bool IsLive();
	void IsDead();
	int GetNoteTime();
	eNoteStatus GetNoteStatus();
	int GetlengthTick();
	void Judged();
	bool IsJudge();
	float GetSecStart();
	Mix_Chunk* GetMusicBGM();
};