#include"TrackSettingCSV.h"
#include<stdio.h>
#include<string.h>
TrackSettingCSV::TrackSettingCSV()
{
	
}

TrackSettingCSV::~TrackSettingCSV()
{
}
void TrackSettingCSV::CSVParsing()
{
	char filePath[256];
	sprintf(filePath, "../Resources/%s", "trackSetting.csv");
	FILE* fp = fopen(filePath, "r");
	if (NULL == fp)
	{
		printf("File 안열림 에러\n");
	}
	char buffer[1024];
	char * record = fgets(buffer, sizeof(buffer), fp);
	while (true)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;
		{
			char* token = strtok(record, ",\n");
			if (!strcmp(token, "Track"))
			{
				token = strtok(NULL, ",\n");
				strcpy(_trackFileName, token);
			}
			else if (!strcmp(token, "Judgeline"))
			{
				token = strtok(NULL, ",\n");
				strcpy(_collisionName, token);
			}
			else if (!strcmp(token, "Explosion"))
			{
				token = strtok(NULL, ",\n");
				strcpy(_noteBoomName, token);
			}
		}
	}
	fclose(fp);
}
char* TrackSettingCSV::GetTrackFileName()
{
	return _trackFileName;
}
char* TrackSettingCSV::GetCollisionName()
{
	return _collisionName;
}
char* TrackSettingCSV::GetNoteBoomName()
{
	return _noteBoomName;
}