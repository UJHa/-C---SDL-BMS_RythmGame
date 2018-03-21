#pragma once
#include<SDL_mixer.h>
#include<string>
#include<map>
#include<vector>
using namespace std;
class Font;
class Wav;
#include "NumbersSprite.h"
class SettingGamePlay
{
	//Singleton
private:
	static SettingGamePlay* _instance;
public:
	static SettingGamePlay* GetInstance();
private:
	SettingGamePlay();
public:
	~SettingGamePlay();
	//Game Info
private:
	string _fileRoute;
	string _BMSname;
public:
	string GetBMS(){ return _BMSname; }
	void ResetData();
	void ResetData(string fileRoute, string fileBMS);
	void Dinit();
	//bmsFile
private:
	FILE* _bmsFile;
public:
	FILE* GetFilePointerBMS();
	//Setting gameTime 
private:
	int _timeTick;
public:
	void SetGameTimeTick(float sec) { _timeTick = (int)(sec * 1000.0f); }
	int GetGameTimeTick() { return _timeTick; }
	//Setting trackHeight
private:
	int _trackHeight;
public:
	void SetTrackHeight(int height) { _trackHeight = height; }
	int GetTrackHeight() { return _trackHeight; }
	//Setting combo
private:
	int _comboNum;
	int _maxComboNum;
public:
	int GetComboNum() { return _comboNum; }
	int GetMaxComboNum() { return _maxComboNum; }
	void AddCombo();
	void ResetCombo() { _comboNum = 0; }
	//Setting Constant value
public:
	float GetGameLoadTime() { return 1.0f; }
	int GetCollisionDeltaLine();
	//Setting font
private:
	std::vector<Font*> _fontList;
public:
	void AppendFontList(Font* font) { _fontList.push_back(font); }
	std::vector<Font*> GetFontList() { return _fontList; }
	//Setting BMS Parsing
private:
	vector<string> _bmsInfo;
	int _measureNum;
	int _channelNum;
	bool _isFileReadFinish;
	vector<string>::iterator _itBms;
public:
	bool SettingData(int deltaTime);
	bool BMSFileRead(int deltaTime);
	bool ParsingBMS(int deltaTime);
	//game setting
private:
	float _gamePlayTime;
	float _measureStandardTimeSec;
	string _longNoteBit;
public:
	float GetMeasureStandardTimeSec() { return _measureStandardTimeSec; }
	string GetLongNoteBit() { return _longNoteBit; }
	//background music setting
private:
	vector<Wav*> _autoWavList;
	map<string, Mix_Chunk*> _wavChunkMap;
	map<float, vector<Mix_Chunk*>> _wavSecMap;
	map<int, vector<string>> _noteInfoMap;
public:
	vector<Wav*> GetWavList() { return _autoWavList; }
	map<int, vector<string>> GetNoteInfoMap() { return _noteInfoMap; }
	map<string, Mix_Chunk*> GetWavMap() { return _wavChunkMap; }
	//effectSprites
private:
	NumbersSprite* _numberSprite;
	vector<Sprite*> _judgeFontSpriteList;
	vector<int> _judgeCountList;
public:
	void SetNumberSprite(NumbersSprite* numberFontSprite) { _numberSprite = numberFontSprite; }
	Sprite* GetJudgeFont(int ejudge) { return _judgeFontSpriteList[ejudge]; }
	void AddJudgeFont(Sprite* sprite) { _judgeFontSpriteList.push_back(sprite); }
	void AddJudgeCount(int judge);
	int GetJudgeCount(int judge);
};