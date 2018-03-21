#pragma once
#include<string>
#include<vector>
using namespace std;
struct Mix_Chunk;
class Wav
{
private:
	float _measureSec;
	int _updateDuration;
	bool _isPlay;
	vector<Mix_Chunk*> _musicBGMList;
public:
	Wav(float measureSec, vector<Mix_Chunk*> musicBGM);
	~Wav();
	void Init();
	void Dinit();
	void Update(int deltaTime);
};