#pragma once
#include<string>
using namespace std;
class Sprite;
class Font;
class FontBox
{
public:
	FontBox(string fileName,string textName);
	~FontBox();

private:
	string _fileName;
	string _textName;
	Sprite* _sprite;
	Font* _font;
public:
	void Init();
	void Render();
	void SetPosition(int x, int y);
	void MovePosition(int x, int y);
};