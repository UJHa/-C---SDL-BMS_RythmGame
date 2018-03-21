#pragma once
#include<list>
using namespace std;
class FontBox;
class MusicList
{
public:
	MusicList();
	~MusicList();

	void Init();
	void Render();
private:
	string _fileRoute;
	list<FontBox*> _musicNameFontList;
	list<string> _musicFileStringList;
	list<string>::iterator _itrFocusMusicFileString;
public:
	void InitMusicNameFontList(string fileRoute);
	void SelectEvent();
	bool IsExtensionBMS();
	bool IncreaseIterator();
	bool DecreaseIterator();

	void SpriteListMovePosition(int x, int y);
	string GetNameBMS() { return (*_itrFocusMusicFileString); }
	string GetFileRoute() { return _fileRoute; }
};

