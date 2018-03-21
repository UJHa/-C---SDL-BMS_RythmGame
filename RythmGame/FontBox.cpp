#include "FontBox.h"
#include "Sprite.h"
#include "Font.h"
FontBox::FontBox(string fileName, string textName)
{
	_fileName = fileName;
	_textName = textName;
}

FontBox::~FontBox()
{
}
void FontBox::Init()
{
	_sprite = new Sprite(_fileName.c_str());
	_sprite->Init();
	_font = new Font("arialbd.ttf", 24);
	_font->SetText(_textName.c_str(), 0, 0, 0);
}
void FontBox::Render()
{
	_sprite->Render();
	_font->Render();
}
void FontBox::SetPosition(int x, int y)
{
	_sprite->SetPosition(x, y);
	_font->SetPosition(x, y);
}
void FontBox::MovePosition(int x, int y)
{
	_sprite->MovePosition(x, y);
	_font->MovePosition(x, y);
}