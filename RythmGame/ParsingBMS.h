//#pragma once
//#include<SDL_mixer.h>
//#include<string>
//#include<map>
//#include<vector>
//using namespace std;
//class Wav;
//class ParsingBMS
//{
//public:
//	ParsingBMS();
//	~ParsingBMS();
//private:
//	vector<string> _headerDataInfoList;
//	vector<string> _mainDataInfoList;
//	map<string, Mix_Chunk*> _wavMap;
//	map<string, string> _noteInfoMap;
//	int _measureNum;
//	int _channelNum;
//public:
//	void Init();
//	void Dinit();
//
//	void BMSFileRead(char* filePathBMS);
//	void SettingHeaderData();
//	void SettingMainData();
//
//	map<string, string> GetNoteInfoMap() { return _noteInfoMap;}
//	map<string, Mix_Chunk*> GetWavMap() { return _wavMap; }
//	//game setting
//private:
//	float _gamePlayTime;
//	int _bpm;
//	float _measureStandardTimeSec;
//public:
//	float GetMeasureStandardTimeSec() { return _measureStandardTimeSec; }
//	//background music setting
//private:
//	vector<Wav*> _wavList;
//public:
//	vector<Wav*> GetWavList() { return _wavList; }
//};