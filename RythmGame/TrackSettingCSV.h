#pragma once
class TrackSettingCSV
{
private:
	char _trackFileName[256];
	char _collisionName[256];
	char _noteBoomName[256];
public:
	TrackSettingCSV();
	~TrackSettingCSV();
	void CSVParsing();
	char* GetTrackFileName();
	char* GetCollisionName();
	char* GetNoteBoomName();
};