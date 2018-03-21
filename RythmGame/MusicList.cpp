#include<io.h>
#include "MusicList.h"
#include "Font.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "FontBox.h"
MusicList::MusicList()
{
	_musicNameFontList.clear();
	_fileRoute = "../Resources/BMS";
}

MusicList::~MusicList()
{
	for (std::list<FontBox*>::iterator it = _musicNameFontList.begin(); it != _musicNameFontList.end(); it++)
	{
		delete (*it);
	}
	_musicNameFontList.clear();
}
void MusicList::Init()
{
	InitMusicNameFontList(_fileRoute + "/*");
}
void MusicList::Render()
{
	for (std::list<FontBox*>::iterator it = _musicNameFontList.begin(); it != _musicNameFontList.end(); it++)
	{
		(*it)->Render();
	}
}

void MusicList::InitMusicNameFontList(string fileRoute)
{
	_musicNameFontList.clear();
	_musicFileStringList.clear();
	_finddata_t fd;
	long handle;
	int result = 1;
	handle = _findfirst(fileRoute.c_str(), &fd);

	if (handle == -1)
		return;
	int interval = 0;
	while (result != -1)
	{
		string dotCheck = fd.name;
		if (!dotCheck.compare(".") || !dotCheck.compare(".."))
		{
			result = _findnext(handle, &fd);
			continue;
		}
		_musicFileStringList.push_back(fd.name);

		FontBox* fontBox = new FontBox("listitemspr.csv", fd.name);
		fontBox->Init();
		fontBox->SetPosition(GameSystem::GetInstance()->GetWidth() / 2, GameSystem::GetInstance()->GetHeight() / 2 + interval);
		interval += 120;
		_musicNameFontList.push_back(fontBox);
		result = _findnext(handle, &fd);
	}
	_findclose(handle);
	_itrFocusMusicFileString = _musicFileStringList.begin();
}
void MusicList::SelectEvent()
{
	_fileRoute = _fileRoute + "/" + (*_itrFocusMusicFileString);

	InitMusicNameFontList(_fileRoute + "/*.bms");
}
bool MusicList::IsExtensionBMS()
{
	return (*_itrFocusMusicFileString).find(".bms") != string::npos;
}
bool MusicList::IncreaseIterator()
{
	_itrFocusMusicFileString++;
	if (_itrFocusMusicFileString == _musicFileStringList.end())
	{
		_itrFocusMusicFileString--;
		return false;
	}
	return true;
}
bool MusicList::DecreaseIterator()
{
	if (_itrFocusMusicFileString == _musicFileStringList.begin())
		return false;

	_itrFocusMusicFileString--;
	return true;
}
void MusicList::SpriteListMovePosition(int x, int y)
{
	for (std::list<FontBox*>::iterator it = _musicNameFontList.begin(); it != _musicNameFontList.end(); it++)
	{
		(*it)->MovePosition(x, y);
	}
}