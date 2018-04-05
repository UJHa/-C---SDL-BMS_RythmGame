#pragma once
#include <string>
#include<vector>
using namespace std;
class Texture;
class Sprite
{
protected:
	string _fileName;

	vector<Texture*> _textureFrames;
	int _frame;
	int _frameMaxCount;
	int _frameDuration;

	int _x;
	int _y;
	int _updateDuration;

	bool _isLoop;
	bool _isPlay;
	float _pivotX;
	float _pivotY;
public:
	Sprite() {};
	Sprite(string fileName);
	~Sprite();
	void Init();
	virtual void Render();
	virtual void Update(int deltaTime);
	virtual void SetPosition(int x, int y);
	void Play();
	void Stop();

	void SetHeight(int height);
	void SetPivotY(float pivotY);
	int GetWidth();
	int GetHeight();
	void MovePosition(int x, int y);
};